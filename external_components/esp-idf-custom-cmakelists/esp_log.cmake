
set(ESP_LOG_SOURCE_DIR /BuildEspAsLibrary/external_components/esp-idf/components/log)
set(esp_log_includes ${ESP_LOG_SOURCE_DIR}/include
                      "/BuildEspAsLibrary/external_components"
                      "/BuildEspAsLibrary/external_components/esp-idf/components/esp_rom/include"
                      "/BuildEspAsLibrary/external_components/esp-idf/components/esp_rom/include/linux"
                      "/BuildEspAsLibrary/external_components/esp-idf/components/soc/linux/include"
                      "/BuildEspAsLibrary/external_components/esp-idf/components/esp_common/include"

                      "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/FreeRTOS-Kernel/include"
                      "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/config/include/freertos"
                      "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/config/include"
                      "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/config/linux/include"
                      "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/FreeRTOS-Kernel/portable/linux/include"
                      "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/FreeRTOS-Kernel/portable/linux/include/freertos"

                      "/BuildEspAsLibrary/external_components/esp-idf/components/esp_system/include"
                      "/BuildEspAsLibrary/external_components/esp-idf/components/esp_hw_support/include"
                      )

set(esp_log_sources ${ESP_LOG_SOURCE_DIR}/log.c ${ESP_LOG_SOURCE_DIR}/log_buffers.c ${ESP_LOG_SOURCE_DIR}/log_linux.c)

# For now we pull in sources specifically, but goal would be to glob files i think
# file(GLOB esp_log_sources ${ESP_LOG_SOURCE_DIR}/*.c)

add_library(esp_log STATIC ${esp_log_sources})
target_include_directories(esp_log PUBLIC ${esp_log_includes})
target_compile_definitions(esp_log PUBLIC TARGET_LINUX=1)