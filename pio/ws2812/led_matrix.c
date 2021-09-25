#include "pico/stdlib.h"
#include "led_matrix.h"

uint32_t image[ROWS][COLUMNS];
uint32_t flattened_data[ROWS * COLUMNS];



void init_test_image()
{
    bool light_row = true;

    for(int i = 0; i < ROWS; i++)
    {
        if(light_row)
        {
            for(int j = 0; j < COLUMNS; j++)
            {
                image[i][j] = 0xffffff;
            }
        } else {
            for (int j = 0; j < COLUMNS; j++)
            {
                image[i][j] = 0;
            }
        }

        light_row = !light_row;
    }
}

// transfer data from image matrix to flattened
// array 
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
                flattened_data[(i * (COLUMNS - 1)) + i + j] = image[i][j];
            }
        } else {
            for(int j = 0; j < COLUMNS; j++)
            {
                flattened_data[(i * (COLUMNS - 1)) + i + j] = image[i][j];
            }

        }

    }
    

}