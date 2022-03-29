#include "pico/stdlib.h"

#ifndef _LED_MATRIX_
#define _LED_MATRIX_

#define RED     {255,0,0}
#define BLUE   {0,255,0}
#define GREEN    {0,0,255}

#define ROWS_IMAGE 32
#define COLUMNS_IMAGE 32

#define ROWS_PANEL 32
#define COLUMNS_PANEL 8

#define PANELS 4
#define VERTICAL 1

extern uint32_t image[ROWS_IMAGE][COLUMNS_IMAGE];
extern uint32_t flattened_data[ROWS_IMAGE * COLUMNS_IMAGE];

typedef struct {
        uint8_t red;
        uint8_t blue;
        uint8_t green;
} Colour;

typedef struct {
        uint8_t x;
        uint8_t y;
} Position;

typedef struct {
        uint8_t height;
        uint8_t width;
        Position origin;
        Colour colour;
} Square;


void init_blank_image();
void init_test_image();
void test_image_horizontal();
void test_image_vertical();
void prepare_data_for_panel();
void prepare_data_for_panel2(int panel);
void prepare_data_for_screen();
void squares_image();
void image_from_uart();
void process_read_buffer();

#endif