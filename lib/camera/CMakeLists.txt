project(camera)
cmake_minimum_required(VERSION 3.26)

FILE(GLOB lib_sources pixel_storer.hpp pixel_storer.cc)
add_library(camera_lib ${lib_sources})

# To have this as part of an esp project, I need to figure out how to add this as external project and link accordingly.
# add_subdirectory("/Users/aryehzapinsky/Devel/esp32_wokwi/BuildEspAsLibrary/external_components/googletest" "./build/external_components/googletest")

add_executable(
  pixel_storer_test
  pixel_storer_test.cc
)

# target_link_libraries(
#   pixel_storer_test
#   GTest::gtest_main
# )

# target_link_libraries(
#   pixel_storer_test
#   GTest::gmock
# )

# target_link_libraries(
#   pixel_storer_test
#   GTest::gtest
# )

# include_directories("/Users/aryehzapinsky/Devel/esp32_wokwi/BuildEspAsLibrary/external_components/googletest/googletest/include")
# include_directories("/Users/aryehzapinsky/Devel/esp32_wokwi/BuildEspAsLibrary/external_components/googletest/googletest")
# target_link_libraries(pixel_storer_test gtest)

# set(source_root "/Users/aryehzapinsky/Devel/esp32_wokwi/BuildEspAsLibrary")
set(source_root ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(lib_root ${source_root}/build/lib)
target_link_libraries(pixel_storer_test PUBLIC ${lib_root}/libgtest_main.a
${lib_root}/libgtest.a 
${lib_root}/libgmock_main.a 
${lib_root}/libgmock.a)
target_include_directories(pixel_storer_test PRIVATE ${source_root}/external_components/googletest/googletest/include)
target_include_directories(pixel_storer_test PRIVATE ${source_root}/external_components/googletest/googlemock/include)
# target_compile_options(pixel_storer_test PUBLIC --coverage)

add_executable(
  main_test
  main_test.cc
)
set(source_root ${CMAKE_CURRENT_SOURCE_DIR}/../..)
set(lib_root ${source_root}/build/lib)
target_link_libraries(main_test PUBLIC ${lib_root}/libgtest_main.a
${lib_root}/libgtest.a 
${lib_root}/libgmock_main.a 
${lib_root}/libgmock.a)
target_include_directories(main_test PRIVATE ${source_root}/external_components/googletest/googletest/include)
target_include_directories(main_test PRIVATE ${source_root}/external_components/googletest/googlemock/include)

# target_link_libraries(main_test PUBLIC ${lib_root}/libgtest_main.a
# ${lib_root}/libgtest.a 
# ${lib_root}/libgmock_main.a 
# ${lib_root}/libgmock.a)
# target_include_directories(main_test PRIVATE ${source_root}/external_components/googletest/googletest/include)
# target_include_directories(main_test PRIVATE ${source_root}/external_components/googletest/googlemock/include)

