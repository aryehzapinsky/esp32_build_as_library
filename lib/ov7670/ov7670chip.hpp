#ifndef OV7670CHIP_HPP
#define OV7670CHIP_HPP

#include <stdint.h>

#include "configurations.hpp"
#include "esp_event.h"
#include "esp_event_base.h"

#ifdef __cplusplus
extern "C" {
#endif

enum class Ov7670EventId : uint32_t {
  PixelClockUpdate,
  HorizontalReferenceUpdate,
  VerticalSyncUpdate,
  Unknown,
};

/**
 * @brief Declare of NMEA Parser Event base.
 *
 * Example from:
 * https://github.com/espressif/esp-idf/blob/
 * 903af13e847cd301e476d8b16b4ee1c21b30b5c6/examples/
 * peripherals/uart/nmea0183_parser/main/nmea_parser.h
 *
 */
ESP_EVENT_DECLARE_BASE(ESP_OV7670_EVENT);

class OV7670Chip {
 public:
  OV7670Chip() : pin_configuration_(defaultPinConfiguration) {}
  explicit OV7670Chip(OV7670ChipPinConfiguration* pin_configuration)
      : pin_configuration_(*pin_configuration) {}
  void Init();

  /* @brief */
  void InitializeI2C();

  /* @brief Resets the chip's registers.
   *
   * Sets the reset pin to reset mode, waits 1 millisecond,
   * sets the reset pin to normal mode and then waits 1 millisecond.
   */
  void Reset();

  /**/
  void GenerateTestData();

  /** @brief Get pin configuration. */
  const OV7670ChipPinConfiguration& pin_configuration() const {
    return pin_configuration_;
  }

  /** @brief Get pixel event loop handle. */
  const esp_event_loop_handle_t& pixel_event_loop_handle() const {
    return pixel_event_loop_handle_;
  }

 private:
  void ConfigurePixelEventLoop();

  void ConfigureInputClock();

  void ConfigureEventHandlers();

  void ConfigureHorizontalReference();

  /* @brief Configure the interrupt to trigger on positive edge of clock. */
  void ConfigurePixelClock();

  void ConfigureVerticalSync();

  void ConfigureResetSignal();
  /* @brief Configure the power down signal.
   *
   * 0 or low is normal mode. So configure the pull down resistor.
   */
  void ConfigurePowerDownSignal();

  /* @brief Non-owning reference to pin configuration. */
  const OV7670ChipPinConfiguration& pin_configuration_;

  esp_event_loop_handle_t pixel_event_loop_handle_;
};

#ifdef __cplusplus
}
#endif

#endif  // OV7670CHIP_HPP