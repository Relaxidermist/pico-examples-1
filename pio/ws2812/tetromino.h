#include "utils/led_matrix.h"

#define BLOCK_SIZE 3
#define DESCENT_PERIOD_MS 1000

void initialize_gravity();
void gravity();
void tetromino_i_1(uint8_t pos_y);