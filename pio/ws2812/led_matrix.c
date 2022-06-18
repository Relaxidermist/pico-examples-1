#include "pico/stdlib.h"
#include "led_matrix.h"
#include <string.h>

uint32_t image[ROWS_IMAGE][COLUMNS_IMAGE];
uint32_t flattened_data[ROWS_IMAGE * COLUMNS_IMAGE];


void init_blank_image()
{
    for(int i = 0; i < ROWS_IMAGE; i++)
    {
        for(int j = 0; j < COLUMNS_IMAGE; j++)
        {
            image[i][j] = 0;
        }
    }
}


void init_test_image(uint32_t pixel)
{
    for(int i = 0; i < ROWS_IMAGE; i++)
    {
        for(int j = 0; j < COLUMNS_IMAGE; j++)
        {
            image[i][j] = pixel;
        }
    }
}

void test_image_memset()
{
    static Colour start = RED;
    static Colour middle = BLUE;
    static Colour finish = GREEN;

    static uint8_t start_row = 0;
    static uint8_t finish_row = ROWS_IMAGE - 1;

    Colour pixel;
    Colour gradient_one, gradient_two;

    gradient_one.red = (middle.red - start.red) / COLUMNS_IMAGE;
    gradient_one.green = (middle.green - start.green) / COLUMNS_IMAGE;
    gradient_one.blue = (middle.blue - start.blue) / COLUMNS_IMAGE;

    gradient_two.red = (finish.red - start.red) / COLUMNS_IMAGE;
    gradient_two.green = (finish.green - start.green) / COLUMNS_IMAGE;
    gradient_two.blue = (finish.blue - start.blue) / COLUMNS_IMAGE;

    for(int j = start_row; j < COLUMNS_IMAGE; j++)
    {
        pixel.red = (gradient_one.red * (j - start_row)) + start.red;
        pixel.green = (gradient_one.green * (j - start_row)) + start.green;
        pixel.blue = (gradient_one.blue * (j - start_row)) + start.blue;

        image[0][j] = (uint32_t)((pixel.green) << 16) |
                    (uint32_t)((pixel.red) << 8) |
                    (uint32_t)((pixel.blue));

    }

    for (int j = 0; j < start_row + 1; j++)
    {
        pixel.red = (gradient_two.red * j) + start.red;
        pixel.green = (gradient_two.green * j) + start.green;
        pixel.blue = (gradient_two.blue * j) + start.blue;

        image[0][start_row - j] = (uint32_t)((pixel.green) << 16) |
                    (uint32_t)((pixel.red) << 8) |
                    (uint32_t)((pixel.blue));
    }

    for(int i = 1; i < ROWS_IMAGE; i++)
    {
        memcpy(image[i], image[0], sizeof(uint32_t) * ROWS_IMAGE);
    }


    if(start_row < COLUMNS_IMAGE)
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

    if(finish_row < COLUMNS_IMAGE)
    {
        finish_row++;
    } else {
        finish_row = 0;
    }
}

void test_image_horizontal()
{
    static Colour start = RED;
    static Colour middle = BLUE;
    static Colour finish = GREEN;

    static uint8_t start_row = 0;
    static uint8_t finish_row = 31;

    Colour pixel;
    Colour gradient_one, gradient_two;

    for (int j = 0; j < COLUMNS_IMAGE; j++)
    {
        gradient_one.red = (middle.red - start.red) / ROWS_IMAGE;
        gradient_one.green = (middle.green - start.green) / ROWS_IMAGE;
        gradient_one.blue = (middle.blue - start.blue) / ROWS_IMAGE;

        gradient_two.red = (finish.red - start.red) / ROWS_IMAGE;
        gradient_two.green = (finish.green - start.green) / ROWS_IMAGE;
        gradient_two.blue = (finish.blue - start.blue) / ROWS_IMAGE;

        for(int i = start_row; i < ROWS_IMAGE; i++)
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
    if(start_row < ROWS_IMAGE)
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

    if(finish_row < ROWS_IMAGE)
    {
        finish_row++;
    } else {
        finish_row = 0;
    }
}

void prepare_data_for_panel()
{
    bool flip_row = true;

    for (int i = 0; i < ROWS_IMAGE; i++) 
    {
        flip_row = !flip_row;

        if(flip_row)
        {
            for(int j = COLUMNS_IMAGE - 1; j > -1; j--)
            {
                flattened_data[(i * (COLUMNS_IMAGE - 1)) + i + j] = image[i][(COLUMNS_IMAGE - 1) - j];
            }
        } else {
            for(int j = 0; j < COLUMNS_IMAGE; j++)
            {
                flattened_data[(i * COLUMNS_IMAGE) + j] = image[i][j];
            }

        }

    }
    

}


void prepare_data_for_panel1(int panel_no)
{
    bool flip_row = true;   // Should the row be flipped? This is inverted every row
    int image_col_offset = (COLUMNS_PANEL * panel_no);    // 8 columns in a panel
    int flattened_offset = COLUMNS_PANEL * ROWS_PANEL * panel_no; // led offset in sequence.

    // Iterate over rows in panel
    for (int i = 0; i < ROWS_PANEL; i++)
    {
        // Invert the row
        flip_row = !flip_row;

        if(flip_row)
        {   
            for(int j = 0; j < COLUMNS_PANEL; j++)
            {
                flattened_data[(i * (COLUMNS_PANEL) + ((COLUMNS_PANEL - 1) - j) + flattened_offset)] = image[i][j + image_col_offset];
            }
        } else {
            for(int j = 0; j < COLUMNS_PANEL; j++)
            {
                flattened_data[(i * COLUMNS_PANEL) + j + flattened_offset] = image[i][j + image_col_offset];
            }
        }
    }
}
/*
void prepare_data_for_panel2(int panel_no)
{
    bool flip_row = true;   // Should the row be flipped? This is inverted every row
    int image_col_offset = (COLUMNS_PANEL * panel_no);    // 8 columns in a panel
    int flattened_offset = 2048 + (COLUMNS_PANEL * ROWS_PANEL * panel_no); // led offset in sequence.

    // Iterate over rows in panel
    for (int i = 0; i < ROWS_PANEL; i++)
    {
        // Invert the row
        flip_row = !flip_row;

        if(flip_row)
        {   
            for(int j = 0; j < COLUMNS_PANEL; j++)
            {
                flattened_data[(i * (COLUMNS_PANEL) + ((COLUMNS_PANEL - 1) - j) + flattened_offset)] = image[i + ROWS_PANEL][j + image_col_offset];
            }
        } else {
            for(int j = 0; j < COLUMNS_PANEL; j++)
            {
                flattened_data[(i * COLUMNS_PANEL) + j + flattened_offset] = image[i + ROWS_PANEL][j + image_col_offset];
            }
        }
    }
}
*/


void test_image_vertical()
{
    static Colour start = RED;
    static Colour middle = BLUE;
    static Colour finish = GREEN;

    static uint8_t start_row = 0;
    static uint8_t finish_row = 31;

    Colour pixel;
    Colour gradient_one, gradient_two;

    for (int i = 0; i < ROWS_IMAGE; i++)
    {
        gradient_one.red = (middle.red - start.red) / COLUMNS_IMAGE;
        gradient_one.green = (middle.green - start.green) / COLUMNS_IMAGE;
        gradient_one.blue = (middle.blue - start.blue) / COLUMNS_IMAGE;

        gradient_two.red = (finish.red - start.red) / COLUMNS_IMAGE;
        gradient_two.green = (finish.green - start.green) / COLUMNS_IMAGE;
        gradient_two.blue = (finish.blue - start.blue) / COLUMNS_IMAGE;

        for(int j = start_row; j < COLUMNS_IMAGE; j++)
        {
            pixel.red = (gradient_one.red * (j - start_row)) + start.red;
            pixel.green = (gradient_one.green * (j - start_row)) + start.green;
            pixel.blue = (gradient_one.blue * (j - start_row)) + start.blue;

            image[i][j] = (uint32_t)((pixel.green) << 16) |
                        (uint32_t)((pixel.red) << 8) |
                        (uint32_t)((pixel.blue));

        }

        for (int j = 0; j < start_row + 1; j++)
        {
            pixel.red = (gradient_two.red * j) + start.red;
            pixel.green = (gradient_two.green * j) + start.green;
            pixel.blue = (gradient_two.blue * j) + start.blue;

            image[i][start_row - j] = (uint32_t)((pixel.green) << 16) |
                        (uint32_t)((pixel.red) << 8) |
                        (uint32_t)((pixel.blue));
        }      
    }
    if(start_row < COLUMNS_IMAGE)
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

    if(finish_row < COLUMNS_IMAGE)
    {
        finish_row++;
    } else {
        finish_row = 0;
    }
}


void prepare_data_for_screen()
{
    for(int i = 0; i < PANELS; i++)
    {
        prepare_data_for_panel1(i);
    }
}