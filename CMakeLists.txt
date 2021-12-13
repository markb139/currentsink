# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "/home/pi/pico/pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(currentsink C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(currentsink 
        currentsink.c 
        pwm.c
        adc_voltage.c
        usb_descriptors.c
        usbtmc_app.c
        commands.c
        )

pico_set_program_name(currentsink "currentsink")
pico_set_program_version(currentsink "0.1")

target_include_directories(currentsink PRIVATE ${CMAKE_CURRENT_LIST_DIR})

pico_enable_stdio_uart(currentsink 1)
pico_enable_stdio_usb(currentsink 0)

# Add the standard library to the build
target_link_libraries(currentsink pico_stdlib)

# Add any user requested libraries
target_link_libraries(currentsink
        hardware_i2c
        hardware_dma
        hardware_pwm
        hardware_adc
        tinyusb_device 
        tinyusb_board
        )

pico_add_extra_outputs(currentsink)

