#include "utils/led_matrix.h"

#define BLOCK_SIZE 3
#define DESCENT_PERIOD_MS 250

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