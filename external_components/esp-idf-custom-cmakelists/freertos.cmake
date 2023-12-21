set (FREERTOS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/esp-idf/components/freertos)
set (freertos_includes 
      "${FREERTOS_SOURCE_DIR}/FreeRTOS-Kernel/include/freertos"
      "${FREERTOS_SOURCE_DIR}/config/include/freertos"
      "${FREERTOS_SOURCE_DIR}"
      "${FREERTOS_SOURCE_DIR}/config/linux/include"
      "${FREERTOS_SOURCE_DIR}/FreeRTOS-Kernel/portable/linux/include/freertos"
      "/BuildEspAsLibrary/external_components/esp-idf/components/esp_common/include"
      "/BuildEspAsLibrary/external_components/esp-idf/components/esp_system/include"
      "${FREERTOS_SOURCE_DIR}/FreeRTOS-Kernel/include"
      "${FREERTOS_SOURCE_DIR}/config/include"
      "${FREERTOS_SOURCE_DIR}/FreeRTOS-Kernel/portable/linux/include"
      "${FREERTOS_SOURCE_DIR}/esp_additions/include"
      "/BuildEspAsLibrary/external_components/esp-idf/components/log/include"
      "/BuildEspAsLibrary/external_components/esp-idf/components/esp_rom/include"
      "/BuildEspAsLibrary/external_components/esp-idf/components/esp_rom/include/linux"
      "/BuildEspAsLibrary/external_components/esp-idf/components/esp_system/include"
      "/BuildEspAsLibrary/external_components"
      "/BuildEspAsLibrary/external_components/esp-idf/components/soc/linux/include"
      "/BuildEspAsLibrary/external_components/esp-idf/components/heap/include"
      "/BuildEspAsLibrary/external_components/esp-idf/components/freertos/esp_additions/"

      "/BuildEspAsLibrary/external_components/esp-idf/components/esp_hw_support/include"
            )
file(GLOB_RECURSE freertos_sources ${CMAKE_CURRENT_SOURCE_DIR}/esp-idf/components/freertos/FreeRTOS-Kernel/portable/linux/*.c)
list(APPEND freertos_sources 
        ${FREERTOS_SOURCE_DIR}/FreeRTOS-Kernel/queue.c
        ${FREERTOS_SOURCE_DIR}/FreeRTOS-Kernel/list.c
        ${FREERTOS_SOURCE_DIR}/FreeRTOS-Kernel/tasks.c
        ${FREERTOS_SOURCE_DIR}/FreeRTOS-Kernel/timers.c
        ${FREERTOS_SOURCE_DIR}/FreeRTOS-Kernel/event_groups.c
        ${FREERTOS_SOURCE_DIR}/FreeRTOS-Kernel/stream_buffer.c
        ${FREERTOS_SOURCE_DIR}/heap_idf.c)
add_library(freertos STATIC ${freertos_sources})
target_compile_definitions(freertos PUBLIC ESP_PLATFORM)
target_include_directories(freertos PUBLIC ${freertos_includes})

target_compile_definitions(freertos PUBLIC TARGET_LINUX=1)