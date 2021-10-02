#include "pico/stdlib.h"
#include "led_matrix.h"
#include "led_ring_dots.h"

uint32_t image[ROWS][COLUMNS];
uint32_t flattened_data[ROWS * COLUMNS];


void init_blank_image()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            image[i][j] = 0;
        }
    }
}


void init_test_image()
{
    uint32_t pixel = 0xffffff;

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLUMNS; j++)
        {
            image[i][j] = pixel >> (j * 2);
        }
    }
}

void init_test_image_diagonal()
{
    static Colour start = RED;
    static Colour middle = BLUE;
    static Colour finish = GREEN;

    static uint8_t start_row = 0;
    static uint8_t finish_row = 31;

    Colour pixel;
    Colour gradient_one, gradient_two;

    for (int j = 0; j < COLUMNS; j++)
    {
        gradient_one.red = (middle.red - start.red) / ROWS;
        gradient_one.green = (middle.green - start.green) / ROWS;
        gradient_one.blue = (middle.blue - start.blue) / ROWS;

        gradient_two.red = (finish.red - start.red) / ROWS;
        gradient_two.green = (finish.green - start.green) / ROWS;
        gradient_two.blue = (finish.blue - start.blue) / ROWS;

        for(int i = start_row; i < ROWS; i++)
        {
            pixel.red = (gradient_one.red * (i - start_row)) + start.red;
            pixel.green = (gradient_one.green * (i - start_row)) + start.green;
            pixel.blue = (gradient_one.blue * (i - start_row)) + start.blue;

            image[i][j] = (uint32_t)((pixel.green) << 16) |
                        (uint32_t)((pixel.red) << 8) |
                        (uint32_t)((pixel.blue));

        }

        for (int i = 0; i < start_row + 1; i++)
        {
            pixel.red = (gradient_two.red * i) + start.red;
            pixel.green = (gradient_two.green * i) + start.green;
            pixel.blue = (gradient_two.blue * i) + start.blue;

            image[(start_row) - i][j] = (uint32_t)((pixel.green) << 16) |
                        (uint32_t)((pixel.red) << 8) |
                        (uint32_t)((pixel.blue));
        }      
    }
    if(start_row < ROWS)
    {
        start_row++;
    } else {
        start_row = 0;
        
        Colour temp1, temp2;

        temp1 = start;
        temp2 = middle;

        start = finish;
        middle = temp1;
        finish = temp2;
    }

    if(finish_row < ROWS)
    {
        finish_row++;
    } else {
        finish_row = 0;
    }
}

void prepare_data_for_panel()
{
    bool flip_row = true;

    for (int i = 0; i < ROWS; i++) 
    {
        flip_row = !flip_row;

        if(flip_row)
        {
            for(int j = COLUMNS - 1; j > -1; j--)
            {
                flattened_data[(i * (COLUMNS - 1)) + i + j] = image[i][(COLUMNS - 1) - j];
            }
        } else {
            for(int j = 0; j < COLUMNS; j++)
            {
                flattened_data[(i * COLUMNS) + j] = image[i][j];
            }

        }

    }
    

}