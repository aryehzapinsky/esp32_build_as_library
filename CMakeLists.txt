cmake_minimum_required(VERSION 3.16.0)

unset(CMAKE_CXX_FLAGS)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(VERBOSE ON)

include(/docker_containers/toolchain.cmake)

# set(tools /Users/aryehzapinsky/Devel/esp32_wokwi/llvm_tools/llvm_build_dir)
# set(CMAKE_C_COMPILER ${tools}/bin/clang)
# set(CMAKE_CXX_COMPILER ${tools}/bin/clang)
# set(CMAKE_ASM_COMPILER ${tools}/bin/clang)
# set(CMAKE_AR ${tools}/bin/llvm-ar)

set(CMAKE_EXE_LINKER_FLAGS_INIT "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(cxx_libs /Users/aryehzapinsky/Devel/esp32_wokwi/llvm_tools/llvm_with_cxx)

set(CMAKE_CXX_FLAGS "-Wall")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=${tools}/bin/llvm-link")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(BuildEspAsLibrary)
add_subdirectory(external_components)
add_subdirectory(lib)

add_executable(src.elf src/main.c)

set(external_components_libraries 
                              freertos 
                              esp_hw_support 
                              spi_flash
                              esp_log
                              heap
                              esp_system
                              )

target_link_libraries(src.elf PUBLIC ${external_components_libraries})

# set(PYTHON "/Users/aryehzapinsky/Devel/esp32_wokwi/esp_idf_tools/python_env/idf5.1_py3.10_env/bin/python3")

# set(targets "esp32" "esp32s2" "esp32s3" "esp32c3" "esp32c2" "esp32c6" "esp32h2")

# if("${TARGET}" IN_LIST targets)
#     # Include for ESP-IDF build system functions
#     include($ENV{IDF_PATH}/tools/cmake/idf.cmake)
#     # Create idf::{target} and idf::freertos static libraries
#     idf_build_process("${TARGET}"
#                     # try and trim the build; additional components
#                     # will be included as needed based on dependency tree
#                     #
#                     # although esptool_py does not generate static library,
#                     # processing the component is needed for flashing related
#                     # targets and file generation
#                     COMPONENTS log 
#                     # newlib freertos esptool_py
#                     SDKCONFIG ${CMAKE_CURRENT_LIST_DIR}/sdkconfig
#                     BUILD_DIR ${CMAKE_BINARY_DIR})
# else()
#     message(WARNING "Unknown target ${TARGET}, creating stubs for esp32 instead")
#     add_subdirectory(newlib)
#     # Create stubs for esp32 and freertos, stub::esp32 and stub::freertos
#     add_subdirectory(stubs/esp32)
#     add_subdirectory(stubs/freertos)
#     add_subdirectory(stubs/spi_flash)
# endif()

# set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(elf_file ${CMAKE_PROJECT_NAME}.elf)
# add_executable(${elf_file} src/main.c)

# # Link the static libraries to the executable
# if("${TARGET}" IN_LIST targets)
#     target_link_libraries(${elf_file} idf::freertos idf::spi_flash)
#     # Attach additional targets to the executable file for flashing,
#     # linker script generation, partition_table generation, etc.
#     idf_build_executable(${elf_file})
# else()
#     target_link_libraries(${elf_file} stub::esp32 stub::freertos stub::spi_flash)
# endif()