

set(SPI_FLASH_SOURCE_DIR /BuildEspAsLibrary/external_components/esp-idf/components/spi_flash)
set(spi_flash_includes ${SPI_FLASH_SOURCE_DIR}/include
                      "/BuildEspAsLibrary/external_components/esp-idf/components/esp_common/include"
                      "/BuildEspAsLibrary/external_components"
                      "/BuildEspAsLibrary/external_components/esp-idf/components/hal/include"
                      )
file(GLOB spi_flash_sources ${SPI_FLASH_SOURCE_DIR}/linux/*.c)

add_library(spi_flash STATIC ${spi_flash_sources})
target_include_directories(spi_flash PUBLIC ${spi_flash_includes})