/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include "esp_chip_info.h"
#include "esp_err.h"
#include "esp_event.h"
#include "esp_flash.h"
#include "esp_log.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "portmacro.h"
#include "projdefs.h"
#include <stdio.h>

static esp_event_loop_handle_t loop_handle;
ESP_EVENT_DECLARE_BASE(CAMERA_CAPTURE_EVENT);
ESP_EVENT_DEFINE_BASE(CAMERA_CAPTURE_EVENT);
static int kTASK_PERIOD = 500;
static const char *kTAG = "user_event_loop";

struct CameraEventPixel {
  int index;
  int value;
};

void run_on_event(void *handler_arg, esp_event_base_t base, int32_t id,
                  void *event_data) {

  struct CameraEventPixel event_pixel =
      *((struct CameraEventPixel *)event_data);

  printf("In event loop\n");
  ESP_LOGI(kTAG, "handling pixel index: %d, value %d", event_pixel.index,
           event_pixel.value);
}

static void task_event_source(void *args) {
  ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

  struct CameraEventPixel event_pixel = {50, 100};

  ESP_ERROR_CHECK(esp_event_post_to(loop_handle, CAMERA_CAPTURE_EVENT, 0,
                                    &event_pixel, sizeof(event_pixel),
                                    portMAX_DELAY));

  vTaskDelay(pdMS_TO_TICKS(kTASK_PERIOD));

  // Delete from inside task because wasn't working from outside of task
  vTaskDelete(NULL);
}

void app_main(void) {
  printf("Hello world!\n");

  /* Print chip information */
  esp_chip_info_t chip_info;
  uint32_t flash_size;
  esp_chip_info(&chip_info);
  printf("This is ESP32 chip with %d CPU cores, WiFi%s%s, ", chip_info.cores,
         (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "",
         (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

  unsigned major_rev = chip_info.revision / 100;
  unsigned minor_rev = chip_info.revision % 100;
  printf("silicon revision v%d.%d, ", major_rev, minor_rev);
  if (esp_flash_get_size(NULL, &flash_size) != ESP_OK) {
    printf("Get flash size failed");
    return;
  }

  esp_event_loop_args_t loop_args = {.queue_size = 5,
                                     .task_stack_size = 2048,
                                     .task_name = "Loop_for_pixel_events",
                                     .task_priority = uxTaskPriorityGet(NULL),
                                     .task_core_id = tskNO_AFFINITY};

  ESP_ERROR_CHECK(esp_event_loop_create(&loop_args, &loop_handle));

  ESP_ERROR_CHECK(esp_event_handler_instance_register_with(
      loop_handle, CAMERA_CAPTURE_EVENT, ESP_EVENT_ANY_ID, run_on_event,
      /*event_handler_args=*/NULL, /*esp_event_handler_instance_t=*/NULL));

  printf("%dMB %s flash\n", flash_size / (1024 * 1024),
         (chip_info.features & CHIP_FEATURE_EMB_FLASH) ? "embedded"
                                                       : "external");

  for (int i = 1; i >= 0; i--) {
    printf("Restarting in %d seconds...\n", i);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }

  struct CameraEventPixel pixel_event = {1, 20};
  esp_event_post_to(loop_handle, CAMERA_CAPTURE_EVENT, 0, &pixel_event,
                    sizeof(pixel_event), 10);
  esp_event_post_to(loop_handle, CAMERA_CAPTURE_EVENT, 0, &pixel_event,
                    sizeof(pixel_event), 10);

  TaskHandle_t task_event_source_handle;
  xTaskCreate(task_event_source, "task_event_source", 3072, NULL,
              uxTaskPriorityGet(NULL) + 1, &task_event_source_handle);

  xTaskNotifyGive(task_event_source_handle);

  esp_event_loop_run(loop_handle, 100);

  printf("Restarting now.\n");
  fflush(stdout);
  esp_restart();
}