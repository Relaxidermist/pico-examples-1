
#include "tetromino.h"
#include "pico/stdlib.h"
#include <string.h>

extern uint32_t image[ROWS_IMAGE][COLUMNS_IMAGE];
uint8_t pos_y = 0;
repeating_timer_t timer;
uint8_t tetromino_idx = 0;
enum tetromino_rotations rotation = rotation_0_degrees;
extern const uint32_t tetrimino_i_rot0[][4* BLOCK_SIZE];


void tetromino_i(uint8_t pos_x, enum tetromino_rotations rotation){

    switch(rotation) {
        case rotation_0_degrees:
            for(uint i = 0; i < 4 * BLOCK_SIZE; i++) {
                memcpy(&image[pos_x + i][pos_y], &tetrimino_i_rot0[i], 4 * BLOCK_SIZE * sizeof(uint32_t));
            }
            break;
        case rotation_90_degrees:
            for(uint i = 0; i < 4 * BLOCK_SIZE; i++) {
                memcpy(&image[pos_x + i][pos_y], &tetrimino_i_rot1[i], 4 * BLOCK_SIZE * sizeof(uint32_t));
            }
            break;
        case rotation_180_degrees:
            for(uint i = 0; i < 4 * BLOCK_SIZE; i++) {
                memcpy(&image[pos_x + i][pos_y], &tetrimino_i_rot0[i], 4 * BLOCK_SIZE * sizeof(uint32_t));
            }
            break;
        case rotation_270_degrees:
            for(uint i = 0; i < 4 * BLOCK_SIZE; i++) {
                memcpy(&image[pos_x + i][pos_y], &tetrimino_i_rot1[i], 4 * BLOCK_SIZE * sizeof(uint32_t));
            }
            break;          
    }
}

// teteromino_o is the same in every rotation
void tetromino_o(uint8_t pos_x, enum tetromino_rotations rotation){

    Colour pixel = YELLOW;

    for (uint8_t i = 0; i < BLOCK_SIZE * 2; i++) {
        for(uint8_t j = 0; j < BLOCK_SIZE * 2; j++) {
        image[pos_x + i][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                (uint32_t)((pixel.red) << 8) |
                (uint32_t)((pixel.blue));
        }
    }
}

void tetromino_s(uint8_t pos_x, enum tetromino_rotations rotation){

    Colour pixel = GREEN;

    switch(rotation) {
        case rotation_0_degrees:
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
            break;
        case rotation_90_degrees:
            for (uint8_t i = 0; i < BLOCK_SIZE; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE; j++) {

                    image[pos_x + i][pos_y + j] = (uint32_t)((pixel.green) << 16) |
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
            for (uint8_t i = 0; i < BLOCK_SIZE; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE * 2;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
        case rotation_180_degrees:
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
            break;
        case rotation_270_degrees:
            for (uint8_t i = 0; i < BLOCK_SIZE; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE; j++) {

                    image[pos_x + i][pos_y + j] = (uint32_t)((pixel.green) << 16) |
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
            for (uint8_t i = 0; i < BLOCK_SIZE; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE * 2;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
    }
}

void tetromino_z(uint8_t pos_x, enum tetromino_rotations rotation){

    Colour pixel = RED;

    switch(rotation) {
        case rotation_0_degrees:
            for (uint8_t i = 0; i < BLOCK_SIZE * 2; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    image[pos_x + i][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for (uint8_t i = 0; i < BLOCK_SIZE * 2; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
        case rotation_90_degrees:
            for (uint8_t i = 0; i < BLOCK_SIZE; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE; j++) {

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
            for (uint8_t i = 0; i < BLOCK_SIZE; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    uint8_t y_offset = BLOCK_SIZE * 2;

                    image[pos_x + i][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
        case rotation_180_degrees:
            for (uint8_t i = 0; i < BLOCK_SIZE * 2; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    image[pos_x + i][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for (uint8_t i = 0; i < BLOCK_SIZE * 2; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
        case rotation_270_degrees:
            for (uint8_t i = 0; i < BLOCK_SIZE; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE; j++) {

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
            for (uint8_t i = 0; i < BLOCK_SIZE; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    uint8_t y_offset = BLOCK_SIZE * 2;

                    image[pos_x + i][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
    }


}


void tetromino_j(uint8_t pos_x, enum tetromino_rotations rotation){

    Colour pixel = BLUE;

    switch(rotation) {
        case rotation_0_degrees:
            for(uint8_t i = 0; i < BLOCK_SIZE * 1; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    image[pos_x + i][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }

            for(uint8_t i = 0; i < BLOCK_SIZE * 3; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {
                    
                    uint8_t y_offset = BLOCK_SIZE;

                    image[pos_x + i][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
        case rotation_90_degrees:
            for(uint8_t i = 0; i < BLOCK_SIZE * 2; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    uint8_t x_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE * 1; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {
            
                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE * 1; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {
            
                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE * 2;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
        case rotation_180_degrees:
            for(uint8_t i = 0; i < BLOCK_SIZE * 3; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    image[pos_x + i][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE; j++) {
                    
                    uint8_t x_offset = BLOCK_SIZE * 2;
                    uint8_t y_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
        case rotation_270_degrees:
            for(uint8_t i = 0; i < BLOCK_SIZE; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE; j++) {

                    uint8_t x_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE * 1; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {
            
                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE * 2; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {
            
                    uint8_t y_offset = BLOCK_SIZE * 2;

                    image[pos_x + i][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
    }
}


void tetromino_l(uint8_t pos_x, enum tetromino_rotations rotation){

    Colour pixel = ORANGE;

    switch(rotation) {
        case rotation_0_degrees:
            for(uint8_t i = 0; i < BLOCK_SIZE * 1; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    uint8_t x_offset = BLOCK_SIZE * 2;

                    image[pos_x + i + x_offset][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }

            for(uint8_t i = 0; i < BLOCK_SIZE * 3; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {
                    
                    uint8_t y_offset = BLOCK_SIZE;

                    image[pos_x + i][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
        case rotation_90_degrees:
            for(uint8_t i = 0; i < BLOCK_SIZE; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE; j++) {

                    uint8_t x_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE * 1; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {
            
                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE * 2; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {
            
                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE * 2;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
        case rotation_180_degrees:
            for(uint8_t i = 0; i < BLOCK_SIZE * 3; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE; j++) {

                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE * 1; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {
            
                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE * 2;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
        case rotation_270_degrees:
            for(uint8_t i = 0; i < BLOCK_SIZE * 2; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE; j++) {

                    uint8_t x_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE * 1; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {
            
                    uint8_t x_offset = BLOCK_SIZE * 2;
                    uint8_t y_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE * 1; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {
            
                    uint8_t x_offset = BLOCK_SIZE * 2;
                    uint8_t y_offset = BLOCK_SIZE * 2;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
    }
}

void tetromino_t(uint8_t pos_x, enum tetromino_rotations rotation){

    Colour pixel = PURPLE;

    switch(rotation) {
        case rotation_0_degrees:
            for(uint8_t i = 0; i < BLOCK_SIZE * 1; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    uint8_t x_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE * 3; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    uint8_t y_offset = BLOCK_SIZE;

                    image[pos_x + i][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
        case rotation_90_degrees:
            for(uint8_t i = 0; i < BLOCK_SIZE; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE; j++) {

                    uint8_t x_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE * 2; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE * 1; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE * 2;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
        case rotation_180_degrees:
            for(uint8_t i = 0; i < BLOCK_SIZE * 3; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE; j++) {

                    uint8_t y_offset = BLOCK_SIZE;

                    image[pos_x + i][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE; j++) {

                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE * 2;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE * 1; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE * 2;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
        case rotation_270_degrees:
            for(uint8_t i = 0; i < BLOCK_SIZE; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE; j++) {

                    uint8_t x_offset = BLOCK_SIZE;

                    image[pos_x + i + x_offset][pos_y + j] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE * 2; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    uint8_t y_offset = BLOCK_SIZE;

                    image[pos_x + i][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            for(uint8_t i = 0; i < BLOCK_SIZE * 1; i++) {
                for(uint8_t j = 0; j < BLOCK_SIZE * 1; j++) {

                    uint8_t x_offset = BLOCK_SIZE;
                    uint8_t y_offset = BLOCK_SIZE * 2;

                    image[pos_x + i + x_offset][pos_y + j + y_offset] = (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));
                }
            }
            break;
    }
}

void initialize_gravity() {
    // get user inputs here
    // some function to move/rotate tetrominos
    add_repeating_timer_ms(DESCENT_PERIOD_MS, (repeating_timer_callback_t) &gravity, NULL, &timer);
}

void gravity() {
    pos_y+=BLOCK_SIZE;
    // rotation test hack
    rotation++;
    if(rotation > rotation_270_degrees){
        rotation = rotation_0_degrees;
    }
    if(pos_y >= 50) {
        if(tetromino_idx == 6) {
            tetromino_idx = 0;
        } else {
            tetromino_idx++;
        }
        pos_y = 0;
    }
}