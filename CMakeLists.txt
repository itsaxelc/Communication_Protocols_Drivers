cmake_minimum_required(VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/gcc-arm-none-eabi.cmake)
project(i2c_test C ASM)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME}
    main.c
    UART/usart2.c
    system.c
    startup_stm32l476xx.s
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