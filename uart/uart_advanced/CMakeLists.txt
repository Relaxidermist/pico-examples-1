add_executable(uart_advanced)

# generate the header file into the source tree as it is included in the RP2040 datasheet
pico_generate_pio_header(uart_advanced ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio OUTPUT_DIR ${CMAKE_CURRENT_LIST_DIR}/generated)

target_sources(uart_advanced PRIVATE uart_advanced.c led_matrix.c)

# Pull in our pico_stdlib which pulls in commonly used features
target_link_libraries(uart_advanced PRIVATE
                    pico_stdlib 
                    hardware_uart 
                    hardware_pio
                    )

# create map/bin/hex file etc.
pico_add_extra_outputs(uart_advanced)

# add url via pico_set_program_url
example_auto_set_url(uart_advanced)
# Additionally generate python and hex pioasm outputs for inclusion in the RP2040 datasheet
#add_custom_target(pio_ws2812_datasheet DEPENDS ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py)
#add_custom_command(OUTPUT ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py
#        DEPENDS ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio
#        COMMAND Pioasm -o python ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio ${CMAKE_CURRENT_LIST_DIR}/generated/ws2812.py
#        )
#add_dependencies(pio_ws2812 pio_ws2812_datasheet)