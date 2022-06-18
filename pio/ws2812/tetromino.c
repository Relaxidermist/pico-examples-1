
#include "tetromino.h"
#include "pico/stdlib.h"

extern uint32_t image[ROWS_IMAGE][COLUMNS_IMAGE];
uint8_t pos_y = 0;
repeating_timer_t timer;


void tetromino_i_1(uint8_t pos_x){

    Colour pixel = CYAN;

    for (uint8_t i = 0; i < BLOCK_SIZE; i++) {
        for(uint8_t j = 0; j < BLOCK_SIZE * 4; j++) {
            image[pos_x + i][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                    (uint32_t)((pixel.red) << 8) |
                    (uint32_t)((pixel.blue));
        }
    }
}

void tetromino_o_1(uint8_t pos_x){

    Colour pixel = YELLOW;

    for (uint8_t i = 0; i < BLOCK_SIZE * 2; i++) {
        for(uint8_t j = 0; j < BLOCK_SIZE * 2; j++) {
            image[pos_x + i][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                    (uint32_t)((pixel.red) << 8) |
                    (uint32_t)((pixel.blue));
        }
    }
}

void tetromino_s_1(uint8_t pos_x){

    Colour pixel = RED;

    for (uint8_t i = 0; i < BLOCK_SIZE * 2; i++) {
        for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

            uint8_t x_offset = BLOCK_SIZE;

            image[pos_x + i + x_offset][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                    (uint32_t)((pixel.red) << 8) |
                    (uint32_t)((pixel.blue));
        }
    }

    for (uint8_t i = 0; i < BLOCK_SIZE * 2; i++) {
        for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

            uint8_t y_offset = BLOCK_SIZE;

            image[pos_x + i][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                    (uint32_t)((pixel.red) << 8) |
                    (uint32_t)((pixel.blue));
        }
    }
}

void initialize_gravity() {
    // get user inputs here
    // some function to move/rotate tetrominos
    add_repeating_timer_ms(DESCENT_PERIOD_MS, (repeating_timer_callback_t) &gravity, NULL, &timer);
}

void gravity() {
    pos_y+=BLOCK_SIZE;
    if(pos_y >= 50) pos_y = 0;
}