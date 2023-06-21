#include "ov7670chip.hpp"

#include "configurations.hpp"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_event.h"
#include "esp_event_base.h"
#include "esp_intr_alloc.h"
#include "esp_types.h"
#include "freertos/FreeRTOS.h"
#include "freertos/FreeRTOSConfig.h"
#include "freertos/task.h"
#include "hal/i2c_types.h"
#include "type_traits"
#include "utility"

namespace {
  constexpr int kI2cTimeoutMs = 1000 / portTICK_PERIOD_MS;
  constexpr int kI2cPrimaryPort = 0;
  constexpr int kI2cWriteAddress = 0x42;
  constexpr int kI2cReadAddress = 0x43;
  constexpr int kClockFrequencyI2C = 24'000'000;
  constexpr int rows = 656;     // 640
  constexpr int columns = 488;  // 480
  constexpr int arrays = 2;     // 2 buffers
  constexpr unsigned char pixel_array[arrays][rows][columns] = {};
}  // namespace

void OV7670Chip::Reset() {
  gpio_set_level(static_cast<gpio_num_t>(pin_configuration_.RESET),
                 static_cast<uint32_t>(ResetPinValues::ResetMode));

  // I don't really like using this constant over here. But I guess I need to
  // use it as opposed to xPortGetTickRateHz() until I can find where and how to
  // include that function. I'm not sure I need to hold this for 1 ms
  vTaskDelay(1 / portTICK_PERIOD_MS);

  gpio_set_level(static_cast<gpio_num_t>(pin_configuration_.RESET),
                 static_cast<uint32_t>(ResetPinValues::NormalMode));

  // Need to delay 1 millisecond before reading registers.
  vTaskDelay(1 / portTICK_PERIOD_MS);
}

// https://github.com/espressif/esp-idf/blob/903af13e847cd301e476d8b16b4ee1c21b30b5c6/examples/peripherals/uart/nmea0183_parser/main/nmea_parser.c
//  /* Create Event loop */
//     esp_event_loop_args_t loop_args = {
//         .queue_size = NMEA_EVENT_LOOP_QUEUE_SIZE,
//         .task_name = NULL
//     };
//     if (esp_event_loop_create(&loop_args, &esp_gps->event_loop_hdl) !=
//     ESP_OK) {
//         ESP_LOGE(GPS_TAG, "create event loop faild");
//         goto err_eloop;
//     }
void OV7670Chip::ConfigurePixelEventLoop() {
  esp_event_loop_args_t loop_args = {.queue_size = rows * columns,
                                     .task_name = nullptr,
                                     .task_priority = 0,
                                     .task_stack_size = 0,
                                     .task_core_id = 0};
  esp_event_loop_create(&loop_args, &pixel_event_loop_handle_);
}

void OV7670Chip::Init() {
  ConfigureResetSignal();
  ConfigurePixelEventLoop();
}

void OV7670Chip::ConfigureResetSignal() {
  /*
  GPIO configuration example:
  https://github.com/espressif/esp-idf/blob/17451f1fb3d6485af5113d96b6836a7ce60efee8/examples/peripherals/gpio/generic_gpio/main/gpio_example_main.c
  */
  gpio_config_t configuration = {
      .pin_bit_mask = 1ULL << pin_configuration_.RESET,
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_ENABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_DISABLE,
  };
  gpio_config(&configuration);
}

void OV7670Chip::ConfigurePowerDownSignal() {
  gpio_config_t configuration = {
      .pin_bit_mask = 1ULL << pin_configuration_.PWDN,
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_ENABLE,
      .intr_type = GPIO_INTR_DISABLE,
  };
  gpio_config(&configuration);
}

void OV7670Chip::ConfigureInputClock() {
  gpio_config_t configuration = {
      .pin_bit_mask = 1ULL << pin_configuration_.PWDN,
      .mode = GPIO_MODE_OUTPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_ENABLE,
      .intr_type = GPIO_INTR_DISABLE,
  };
  gpio_config(&configuration);
}

void OV7670Chip::ConfigureHorizontalReference() {
  gpio_config_t pclk_configuration = {
      .pin_bit_mask = 1ULL << pin_configuration_.HREF,
      .mode = GPIO_MODE_INPUT,
      .pull_up_en = GPIO_PULLUP_DISABLE,
      .pull_down_en = GPIO_PULLDOWN_ENABLE,
      .intr_type =
          GPIO_INTR_DISABLE,  // This actually needs to be neg edge, so that
                              // row number can be incremented by 1
  };
  gpio_config(&pclk_configuration);
}

void OV7670Chip::ConfigureVerticalSync() {
  gpio_config_t pclk_configuration = {
      .pin_bit_mask = 1ULL << pin_configuration_.PCLK,
      .mode = GPIO_MODE_INPUT,
      .pull_up_en = GPIO_PULLUP_ENABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_POSEDGE};
  gpio_config(&pclk_configuration);
}

/* @brief Converts eight integer values to one unsigned char representing
 * pixel value.
 *
 * @note What the byte data actually is depends on the selected settings. For
 * example, the first byte of RGB 565 data is R4-R0 in D[7]-D[3] and G5-G3 in
 * D[2]-D[0].
 *
 *
 * @param Eight values of 0 or 1.
 * @return Byte of data.
 */
static unsigned char ConvertGpioLevelToUnsignedChar(int d7, int d6, int d5,
                                                    int d4, int d3, int d2,
                                                    int d1, int d0) {
  unsigned char d_seven = (d7 == 1) ? 0b1000'0000 : 0;
  unsigned char d_six = (d6 == 1) ? 0b0100'0000 : 0;
  unsigned char d_five = (d5 == 1) ? 0b0010'0000 : 0;
  unsigned char d_four = (d4 == 1) ? 0b0001'0000 : 0;
  unsigned char d_three = (d3 == 1) ? 0b0000'1000 : 0;
  unsigned char d_two = (d2 == 1) ? 0b0000'0100 : 0;
  unsigned char d_one = (d1 == 1) ? 0b0000'0010 : 0;
  unsigned char d_zero = (d0 == 1) ? 0b0000'0001 : 0;
  return (d_seven | d_six | d_five | d_four | d_three | d_two | d_one | d_zero);
}

/**
 * @brief Define of NMEA Parser Event base
 *
 *  Example from:
 * https://github.com/espressif/esp-idf/blob/903af13e847cd301e476d8b16b4ee1c21b30b5c6/examples/peripherals/uart/nmea0183_parser/main/nmea_parser.h
 *
 */
ESP_EVENT_DEFINE_BASE(ESP_OV7670_EVENT);

struct InterruptData {
  // The context in which the interrupt was triggered.
  const OV7670Chip *parent = nullptr;

  // Current pixels being processed.
  unsigned char pixels = {};
};

typedef struct {
  esp_event_loop_handle_t event_loop_handle;
  OV7670Chip parent;
  unsigned char pixels;
} esp_ov7670_t;

// https://stackoverflow.com/questions/14589417/can-an-enum-class-be-converted-to-the-underlying-type
template <typename E>
constexpr auto to_underlying(E e) -> typename std::underlying_type<E>::type {
  return static_cast<typename std::underlying_type<E>::type>(e);
}

/* ISR handler From
 * https://github.com/espressif/esp-idf/blob/efe919275e8f4516ffd5f99f9a59e9d3efbae281/examples/peripherals/gpio/generic_gpio/main/gpio_example_main.c
 */
static void gpio_pixel_clock_handler(void *arg) {
  InterruptData *this_ = static_cast<InterruptData *>(arg);

  const OV7670ChipPinConfiguration &pin_configuration =
      this_->parent->pin_configuration();
  int d0 = gpio_get_level(static_cast<gpio_num_t>(pin_configuration.D0));
  int d1 = gpio_get_level(static_cast<gpio_num_t>(pin_configuration.D1));
  int d2 = gpio_get_level(static_cast<gpio_num_t>(pin_configuration.D2));
  int d3 = gpio_get_level(static_cast<gpio_num_t>(pin_configuration.D3));
  int d4 = gpio_get_level(static_cast<gpio_num_t>(pin_configuration.D4));
  int d5 = gpio_get_level(static_cast<gpio_num_t>(pin_configuration.D5));
  int d6 = gpio_get_level(static_cast<gpio_num_t>(pin_configuration.D6));
  int d7 = gpio_get_level(static_cast<gpio_num_t>(pin_configuration.D7));

  unsigned char pixels =
      ConvertGpioLevelToUnsignedChar(d7, d6, d5, d4, d3, d2, d1, d0);
  this_->pixels = pixels;
  esp_event_isr_post_to(this_->parent->pixel_event_loop_handle(),
                        ESP_OV7670_EVENT,
                        to_underlying(Ov7670EventId::PixelClockUpdate),
                        /*event_data=*/this_, sizeof(*this_),
                        /*task_unblocked=*/NULL);
  // xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
}

// static void gpio_vertical_sync_handler(void *arg) {
//   // uint32_t gpio_num = *static_cast<uint32_t *>(arg);
//   // xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);
// }

static void HandlePixelEvent(void* event_handler_arg,
                                        esp_event_base_t event_base,
                                        int32_t event_id,
                                        void* event_data) {

}

void OV7670Chip::ConfigureEventHandlers() {
  esp_event_handler_instance_register_with(pixel_event_loop_handle_,
  ESP_OV7670_EVENT, to_underlying(Ov7670EventId::PixelClockUpdate), /*event_handler=*/&HandlePixelEvent, 
  /*event_handler_arg=*/NULL, /*instance=*/NULL);
}

void OV7670Chip::ConfigurePixelClock() {
  gpio_config_t pclk_configuration = {
      .pin_bit_mask = 1ULL << pin_configuration_.PCLK,
      .mode = GPIO_MODE_INPUT,
      .pull_up_en = GPIO_PULLUP_ENABLE,
      .pull_down_en = GPIO_PULLDOWN_DISABLE,
      .intr_type = GPIO_INTR_POSEDGE,
  };
  gpio_config(&pclk_configuration);

  /* ISR handler From
   * https://github.com/espressif/esp-idf/blob/efe919275e8f4516ffd5f99f9a59e9d3efbae281/examples/peripherals/gpio/generic_gpio/main/gpio_example_main.c
   */
  // install gpio isr service
  gpio_install_isr_service(ESP_INTR_FLAG_LEVEL1);
  // hook isr handler for specific gpio pin
  gpio_isr_handler_add(static_cast<gpio_num_t>(pin_configuration_.PCLK),
                       gpio_pixel_clock_handler, static_cast<void *>(this));
}

void OV7670Chip::InitializeI2C() {
  i2c_config_t configuration;
  configuration.mode = I2C_MODE_MASTER;
  configuration.sda_io_num = static_cast<int>(pin_configuration_.SIOD);
  configuration.sda_pullup_en = GPIO_PULLUP_ENABLE;
  configuration.scl_io_num = static_cast<int>(pin_configuration_.SIOC);
  configuration.scl_pullup_en = GPIO_PULLUP_ENABLE;
  configuration.master.clk_speed = kClockFrequencyI2C;
  i2c_param_config(static_cast<i2c_port_t>(kI2cPrimaryPort), &configuration);

  i2c_driver_install(static_cast<i2c_port_t>(kI2cPrimaryPort), configuration.mode,
                     /*slv_rx_buf_len=*/0,
                     /*slv_tx_buf_len=*/0, /*intr_alloc_flags=*/0);
}

void DeinitializeI2C() { i2c_driver_delete(static_cast<i2c_port_t>(kI2cPrimaryPort)); }

void OV7670Chip::GenerateTestData() {
  // i2c write to register scaling xsc
  // TestPatternScalingXscBitMask::noTestOutput;
  constexpr int size_of_write_buffer = 4;
  constexpr unsigned char write_buffer[size_of_write_buffer] = {
      to_underlying(RegisterAddress::SCALING_XSC),
      to_underlying(TestPatternScalingXscBitMask::eightBarColorBar),
      to_underlying(RegisterAddress::SCALING_YSC),
      to_underlying(TestPatternScalingYscBitMask::eightBarColorBar)};
  i2c_master_write_to_device(static_cast<i2c_port_t>(kI2cPrimaryPort), kI2cWriteAddress, write_buffer,
                             size_of_write_buffer, kI2cTimeoutMs);
  // example to configure and send i2c commands:
  // https://gist.github.com/mws-rmain/2ba434cd2a3f32d6d343c1c60fbd65c8
}
