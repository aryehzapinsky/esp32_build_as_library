
set(ESP_EVENT_SOURCE_DIR /BuildEspAsLibrary/external_components/esp-idf/components/esp_event)
set(esp_event_includes ${ESP_EVENT_SOURCE_DIR}/include
                        "/BuildEspAsLibrary/external_components/esp-idf/components/esp_common/include"
                        "/BuildEspAsLibrary/external_components"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/linux/include"


                        "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/FreeRTOS-Kernel/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/config/include/freertos"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/config/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/config/linux/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/FreeRTOS-Kernel/portable/linux/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/FreeRTOS-Kernel/portable/linux/include/freertos"

                        "/BuildEspAsLibrary/external_components/esp-idf/components/esp_system/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/log/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/esp_rom/include"
                        "/BuildEspAsLibrary/external_components/esp-idf/components/esp_rom/include/linux"

)

file(GLOB esp_event_private_includes ${ESP_EVENT_SOURCE_DIR}/private_include)

file(GLOB esp_event_sources ${ESP_EVENT_SOURCE_DIR}/*.c)

add_library(esp_event STATIC ${esp_event_sources})
target_include_directories(esp_event PUBLIC ${esp_event_includes})
target_include_directories(esp_event PRIVATE ${esp_event_private_includes})