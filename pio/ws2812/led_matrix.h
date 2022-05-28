#include "pico/stdlib.h"

#define ROWS_IMAGE 64
#define COLUMNS_IMAGE 64

#define ROWS_PANEL 32
#define COLUMNS_PANEL 8

#define PANELS 8
#define VERTICAL 1

extern uint32_t image[ROWS_IMAGE][COLUMNS_IMAGE];
extern uint32_t flattened_data[ROWS_IMAGE * COLUMNS_IMAGE];

void init_blank_image();
void init_test_image(uint32_t pixel);
void test_image_memset();
void test_image_horizontal();
void test_image_vertical();
void prepare_data_for_panel();
void prepare_data_for_panel1(int panel);
void prepare_data_for_panel2(int panel);
void prepare_data_for_screen();
void squares_image();