#include "pico/stdlib.h"

#define ROWS_IMAGE 32
#define COLUMNS_IMAGE 24

#define ROWS_PANEL 32
#define COLUMNS_PANEL 8

#define PANELS 3
#define VERTICAL 1

extern uint32_t image[ROWS_IMAGE][COLUMNS_IMAGE];
extern uint32_t flattened_data[ROWS_IMAGE * COLUMNS_IMAGE];

void init_blank_image();
void init_test_image();
void test_image_horizontal();
void test_image_vertical();
void prepare_data_for_panel();
void prepare_data_for_panel2(int panel);
void prepare_data_for_screen();
void squares_image();