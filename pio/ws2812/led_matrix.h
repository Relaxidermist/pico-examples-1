#include "pico/stdlib.h"

#define ROWS 32
#define COLUMNS 8

extern uint32_t flattened_data[ROWS * COLUMNS];

void init_test_image();
void prepare_data_for_panel();