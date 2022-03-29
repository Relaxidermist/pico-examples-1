/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/irq.h"
#include <stdio.h>
#include "led_matrix.h"
#include "ws2812.pio.h"


/// \tag::uart_advanced[]

#define UART_ID uart1
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 4
#define UART_RX_PIN 5

#define BUFFER_SIZE 3072

uint8_t buffered_chars[BUFFER_SIZE];
char str[3072];
static bool buffer_full;
const uint LED_PIN = PICO_DEFAULT_LED_PIN;
void write_panel();


static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

void write_panel()
{
    for(int i = 0; i < ROWS_IMAGE * COLUMNS_IMAGE; i++)
    {
        put_pixel(flattened_data[i]);
    }
}


// RX interrupt handler
void on_uart_rx() {
    static uint16_t i = 0;
    static uint8_t n_bytes = 0;
    for(uint8_t bytes = 0; 0 != (n_bytes = uart_is_readable(UART_ID)); bytes++)
    {
        if(i >= BUFFER_SIZE - 1) 
        {
            buffer_full = true;
            break;
        }
        uart_read_blocking(UART_ID, &buffered_chars[i], n_bytes);
        i += n_bytes;
    }
    if (uart_is_writable(UART_ID)) {
            // Change it slightly first!
            sprintf(str, "%d\n", i);
            uart_puts(UART_ID, str);
    }
}

void print_buffered_chars()
{   for(int i = 0; i < BUFFER_SIZE; i++)
    {
        sprintf(str, "%d: %d\n", i, buffered_chars[i]);
        uart_puts(UART_ID, str);
        //uart_putc(UART_ID, buffered_chars[i]);
        //uart_putc(UART_ID, ' ');
    }
}

int main() {

    stdio_init_all();

    buffer_full = false;
    // Set up our UART with a basic baud rate.
    uart_init(UART_ID, 2400);

    // Set the TX and RX pins by using the function select on the GPIO
    // Set datasheet for more information on function select
    gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

    // Actually, we want a different speed
    // The call will return the actual baud rate selected, which will be as close as
    // possible to that requested
    int __unused actual = uart_set_baudrate(UART_ID, BAUD_RATE);

    // Set UART flow control CTS/RTS, we don't want these, so turn them off
    uart_set_hw_flow(UART_ID, false, false);

    // Set our data format
    uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);

    // Turn off FIFO's - we want to do this character by character
    uart_set_fifo_enabled(UART_ID, true);

    // Set up a RX interrupt
    // We need to set up the handler first
    // Select correct interrupt for the UART we are using
    int UART_IRQ = UART_ID == uart0 ? UART0_IRQ : UART1_IRQ;

    // And set up and enable the interrupt handlers
    irq_set_exclusive_handler(UART_IRQ, on_uart_rx);
    irq_set_enabled(UART_IRQ, true);

    // Now enable the UART to send interrupts - RX only
    uart_set_irq_enables(UART_ID, true, false);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, 0, 800000, false);

    while (1) {
        gpio_put(LED_PIN, 1);
        sleep_ms(100);
        gpio_put(LED_PIN, 0);
        sleep_ms(100);
        if(buffer_full)
        {
            //irq_set_enabled(UART_IRQ, false);
            process_read_buffer();
            //print_buffered_chars();
            //test_image_vertical();
            prepare_data_for_screen();
            write_panel();


        } else {           
        }
        //tight_loop_contents();
    }
}

/// \end:uart_advanced[]
