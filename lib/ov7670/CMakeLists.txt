# idf_component_register(SRCS "ov7670chip.cpp"
#                        INCLUDE_DIRS ".")


# idf_build_get_property(python PYTHON)
# message(STATUS "The Python intepreter is: ${python}")

# freertos is already included in the requirements with idf_component_register.
FILE(GLOB_RECURSE lib_sources ${CMAKE_SOURCE_DIR}/lib/*.*)

set(components "/Users/aryehzapinsky/Devel/esp32_wokwi/esp_git_tools/esp-idf/components")
set(sdkconfig_file "/Users/aryehzapinsky/Devel/esp32_wokwi/Camera/copied_config")

add_library(ov7670_lib ${lib_sources})

# soc can be linux
target_include_directories(ov7670_lib 
PRIVATE 
${sdkconfig_file}
${components}/freertos/FreeRTOS-Kernel/include
${components}/freertos/esp_additions/include/freertos
${components}/freertos/esp_additions/arch/linux/include
${components}/freertos/FreeRTOS-Kernel/include
${components}/freertos/esp_additions/include
${components}/freertos/FreeRTOS-Kernel/portable/linux/include
${components}/esp_event/include
${components}/esp_common/include
${components}/esp_system/include
${components}/esp_system/include
${components}/driver/gpio/include
${components}/esp_hw_support/include
${components}/soc/esp32/include
${components}/hal/include
${components}/esp_rom/include
${components}/driver/i2c/include
)

target_link_libraries(ov7670_lib PUBLIC libdriver)