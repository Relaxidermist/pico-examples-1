#include "utils/led_matrix.h"

#define BLOCK_SIZE 3
#define DESCENT_PERIOD_MS 250

void initialize_gravity();
void gravity();
void tetromino_i_1(uint8_t pos_y);
void tetromino_o_1(uint8_t pos_y);
void tetromino_s_1(uint8_t pos_y);
void tetromino_z_1(uint8_t pos_y);
void tetromino_j_1(uint8_t pos_y);
void tetromino_l_1(uint8_t pos_y);
void tetromino_t_1(uint8_t pos_y);