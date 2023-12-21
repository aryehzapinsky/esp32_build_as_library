

set(ESP_SYSTEM_SOURCE_DIR /BuildEspAsLibrary/external_components/esp-idf/components/esp_system)
set(esp_system_includes ${ESP_SYSTEM_SOURCE_DIR}/include
                        "/BuildEspAsLibrary/external_components/esp-idf/components/esp_common/include"
                        "/BuildEspAsLibrary/external_components"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/FreeRTOS-Kernel/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/config/include/freertos"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/config/linux/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/FreeRTOS-Kernel/portable/linux/include/freertos"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/config/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/FreeRTOS-Kernel/portable/linux/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/heap/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/log/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/esp_rom/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/esp_rom/include/linux"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/esp_hw_support/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/efuse/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/efuse/linux/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/soc/linux/include"

                        "/BuildEspAsLibrary/external_components/esp-idf/components/esp_system/port/include/private"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/esp_system/port/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/hal/linux/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/esp_rom/linux"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/esp_mm/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/hal/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/spi_flash/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/soc/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/hal/platform_port/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/bootloader_support/bootloader_flash/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/bootloader_support/include"
)

set(esp_system_sources
                      "${ESP_SYSTEM_SOURCE_DIR}/esp_system.c"
                      "${ESP_SYSTEM_SOURCE_DIR}/port/soc/linux/reset_reason.c"
                      "${ESP_SYSTEM_SOURCE_DIR}/port/soc/linux/system_internal.c"
                      ${ESP_SYSTEM_SOURCE_DIR}/port/esp_system_linux.c
                      ${ESP_SYSTEM_SOURCE_DIR}/esp_system.c
                      )

add_library(esp_system STATIC ${esp_system_sources})
target_include_directories(esp_system PUBLIC ${esp_system_includes})

target_compile_definitions(esp_system PUBLIC IDF_VER=\"${idf_ver}\")
