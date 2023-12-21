

set(HEAP_SOURCE_DIR /BuildEspAsLibrary/external_components/esp-idf/components/heap)
set(heap_includes ${HEAP_SOURCE_DIR}/include
                      "/BuildEspAsLibrary/external_components/esp-idf/components/esp_common/include"
                      "/BuildEspAsLibrary/external_components"
                      )
file(GLOB heap_sources ${HEAP_SOURCE_DIR}/heap_caps_linux.c)

add_library(heap STATIC ${heap_sources})
target_include_directories(heap PUBLIC ${heap_includes})