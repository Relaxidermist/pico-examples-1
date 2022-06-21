#ifndef TETROMINO_H
#define TETROMINO_H

#include "utils/led_matrix.h"

#define BLOCK_SIZE 3
#define DESCENT_PERIOD_MS 1000

void initialize_gravity();
void gravity();

enum tetromino_rotations{rotation_0_degrees=0,
                        rotation_90_degrees=1, 
                        rotation_180_degrees=2,
                        rotation_270_degrees=3};

void tetromino_i(uint8_t pos_y, enum tetromino_rotations rotation);
void tetromino_o(uint8_t pos_y, enum tetromino_rotations rotation);
void tetromino_s(uint8_t pos_y, enum tetromino_rotations rotation);
void tetromino_z(uint8_t pos_y, enum tetromino_rotations rotation);
void tetromino_j(uint8_t pos_y, enum tetromino_rotations rotation);
void tetromino_l(uint8_t pos_y, enum tetromino_rotations rotation);
void tetromino_t(uint8_t pos_y, enum tetromino_rotations rotation);

// Hardcoded arrays for Tetrominos
// Tetrimino I
static const uint32_t tetrimino_i_rot0[4 * BLOCK_SIZE][4 * BLOCK_SIZE] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT},
    {CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT},
    {CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT, CYAN_INT},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

static const uint32_t tetrimino_i_rot1[4 * BLOCK_SIZE][4 * BLOCK_SIZE] = {
    {0, 0, 0, 0, 0, 0, CYAN_INT, CYAN_INT, CYAN_INT, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, CYAN_INT, CYAN_INT, CYAN_INT, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, CYAN_INT, CYAN_INT, CYAN_INT, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, CYAN_INT, CYAN_INT, CYAN_INT, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, CYAN_INT, CYAN_INT, CYAN_INT, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, CYAN_INT, CYAN_INT, CYAN_INT, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, CYAN_INT, CYAN_INT, CYAN_INT, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, CYAN_INT, CYAN_INT, CYAN_INT, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, CYAN_INT, CYAN_INT, CYAN_INT, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, CYAN_INT, CYAN_INT, CYAN_INT, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, CYAN_INT, CYAN_INT, CYAN_INT, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, CYAN_INT, CYAN_INT, CYAN_INT, 0, 0, 0},
};

#endif /* !TETROMINO_H */