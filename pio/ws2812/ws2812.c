/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "ws2812.pio.h"
#include "tetromino.h"

extern uint32_t flattened_data[];
const void *p_data = &flattened_data;
uint32_t received_data[ROWS_IMAGE * COLUMNS_IMAGE];
queue_t q;
const int PIN_TX = 0;

static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

void write_panel(uint32_t *received_data)
{
    for(int i = 0; i < ROWS_IMAGE * COLUMNS_IMAGE; i++)
    {
        put_pixel(received_data[i]);
    }
}

void image_processing_core1() {

    queue_init(&q, sizeof(uint32_t) * ROWS_IMAGE * COLUMNS_IMAGE, 1);

    initialize_gravity();

    while(1){
        init_blank_image();
        //tetromino_i_1(5);
        //tetromino_o_1(7);
        tetromino_s_1(9);
        //test_image_horizontal();
        prepare_data_for_screen();
        queue_add_blocking(&q, p_data);
    }
}


int main() {

    stdio_init_all();

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, PIN_TX, 800000, false);

    multicore_launch_core1(image_processing_core1);

    while (1) {
        queue_remove_blocking(&q, received_data);   
        write_panel(received_data);
        sleep_us(500);
        }
}



