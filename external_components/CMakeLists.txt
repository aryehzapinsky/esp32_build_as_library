add_subdirectory(googletest)

# include(esp-idf.cmake)
# Build sdkconfig.h before building rtos
# python -m kconfgen --kconfig external_components/esp-idf/components/freertos/Kconfig --output header external_components/esp-idf/components/freertos/sdkconfig.h
#
# Actual command now:
# python -m kconfgen --kconfig external_components/Kconfig --output header external_components/sdkconfig.h

include(esp-idf-custom-cmakelists/freertos.cmake)
include(esp-idf-custom-cmakelists/build_version.cmake)
include(esp-idf-custom-cmakelists/esp_hw_support.cmake)
include(esp-idf-custom-cmakelists/spi_flash.cmake)
include(esp-idf-custom-cmakelists/esp_log.cmake)
include(esp-idf-custom-cmakelists/heap.cmake)
include(esp-idf-custom-cmakelists/esp_system.cmake)

include(esp-idf-custom-cmakelists/esp_common.cmake)
include(esp-idf-custom-cmakelists/esp_event.cmake)


# set(google_test_include_dirs
#   "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include"
#   "${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include"
#   )
# include_directories(${google_test_include_dirs})
# file(GLOB_RECURSE google_test_headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
# file(GLOB_RECURSE google_test_sources ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/*.cc)
# file(GLOB_RECURSE google_mock_sources ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/src/*.cc)
# add_library(google-test STATIC ${google_test_sources} ${google_mock_sources} ${google_test_headers})
# target_include_directories(google-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest)
# target_include_directories(google-test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock)
