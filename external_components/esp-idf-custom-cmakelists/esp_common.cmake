set(ESP_COMMON_SOURCE_DIR /BuildEspAsLibrary/external_components/esp-idf/components/esp_common)
set(esp_common_includes ${ESP_COMMON_SOURCE_DIR}/include
                        "/BuildEspAsLibrary/external_components"
)

set(esp_common_sources ${ESP_COMMON_SOURCE_DIR}/src/esp_err_check_linux.c)

add_library(esp_common STATIC ${esp_common_sources})
target_include_directories(esp_common PUBLIC ${esp_common_includes})