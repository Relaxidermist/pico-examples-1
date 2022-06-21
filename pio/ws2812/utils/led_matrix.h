#include "pico/stdlib.h"

#define ROWS_IMAGE 32
#define COLUMNS_IMAGE 64

#define ROWS_PANEL 32
#define COLUMNS_PANEL 8

#define PANELS 8
#define VERTICAL 1

// Colours
#define NONE_INT    0x0
#define CYAN_INT    0x4B004B


#define RED     {75,0,0}
#define BLUE   {0,75,0}
#define GREEN    {0,0,75}
#define CYAN    {0,75,75}
#define YELLOW   {75,0,75}
#define ORANGE  {75,0,18}
#define PURPLE  {38,38,0}

extern uint32_t image[ROWS_IMAGE][COLUMNS_IMAGE];
extern uint32_t flattened_data[ROWS_IMAGE * COLUMNS_IMAGE];

void init_blank_image();
void init_test_image(uint32_t pixel);
void test_image_memset();
void test_image_horizontal();
void test_image_vertical();
void prepare_data_for_panel();
void prepare_data_for_panel1(int panel);
void prepare_data_for_screen();
void squares_image();

typedef struct {
        uint8_t red;
        uint8_t blue;
        uint8_t green;
} Colour;

