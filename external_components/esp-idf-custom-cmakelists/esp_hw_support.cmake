


set(ESP_HW_SUPPORT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/esp-idf/components/esp_hw_support)
set(esp_hw_support_includes ${ESP_HW_SUPPORT_SOURCE_DIR}/include
                            "/BuildEspAsLibrary/external_components/esp-idf/components/esp_common/include"
                            "/BuildEspAsLibrary/external_components"
                            "/BuildEspAsLibrary/external_components/esp-idf/components/linux/include"
                            "/BuildEspAsLibrary/external_components/esp-idf/components/log/include"
                            "/BuildEspAsLibrary/external_components/esp-idf/components/esp_rom/include"
                            "/BuildEspAsLibrary/external_components/esp-idf/components/esp_rom/include/linux"
                            "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/FreeRTOS-Kernel/include"
                            "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/config/include/freertos"
                            "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/config/include"
                            "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/config/linux/include"
                            "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/FreeRTOS-Kernel/portable/linux/include/freertos"
                            "/BuildEspAsLibrary/external_components/esp-idf/components/esp_system/include"
                            "/BuildEspAsLibrary/external_components/esp-idf/components/soc/linux/include"
                                  )
file(GLOB esp_hw_support_sources ${ESP_HW_SUPPORT_SOURCE_DIR}/port/linux/*.c)

add_library(esp_hw_support STATIC ${esp_hw_support_sources})
target_include_directories(esp_hw_support PUBLIC ${esp_hw_support_includes})

