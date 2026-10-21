cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/gcc-arm-none-eabi.cmake)
project(communication_protocols C ASM)

set(CMAKE_C_STANDARD 11)

# Example to build into the firmware: lcd, uart, ...
# Usage: cmake --preset Debug -DEXAMPLE=uart
set(EXAMPLE "lcd" CACHE STRING "Example to build (file examples/example_<name>.c)")

set(EXAMPLE_SOURCE ${CMAKE_SOURCE_DIR}/examples/example_${EXAMPLE}.c)
if(NOT EXISTS ${EXAMPLE_SOURCE})
    message(FATAL_ERROR "Example '${EXAMPLE}' not found: ${EXAMPLE_SOURCE}")
endif()
message(STATUS "Building example: ${EXAMPLE}")

# Driver sources (re-run cmake if you add a new .c file)
file(GLOB DRIVER_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/I2C/*.c
    ${CMAKE_SOURCE_DIR}/SPI/*.c
    ${CMAKE_SOURCE_DIR}/UART/*.c
    ${CMAKE_SOURCE_DIR}/MPU9250_driver/*.c
    ${CMAKE_SOURCE_DIR}/lcd1602_driver/*.c
)

add_executable(${PROJECT_NAME}
    ${EXAMPLE_SOURCE}
    ${DRIVER_SOURCES}
    system.c
    startup_stm32l476xx.s
)

# Both "i2c1.h" and "I2C/i2c1.h" style includes work with this
target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/I2C
    ${CMAKE_SOURCE_DIR}/SPI
    ${CMAKE_SOURCE_DIR}/UART
    ${CMAKE_SOURCE_DIR}/MPU9250_driver
    ${CMAKE_SOURCE_DIR}/lcd1602_driver
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
    -Wall -Wextra -Og -g3
)

target_link_options(${PROJECT_NAME} PRIVATE
    -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
    -T${CMAKE_SOURCE_DIR}/STM32L476RGTx_FLASH.ld
    -Wl,--gc-sections -Wl,-Map=${PROJECT_NAME}.map
    --specs=nano.specs --specs=nosys.specs
)