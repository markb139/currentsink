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

target_include_directories(currentsink PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/include
)

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

