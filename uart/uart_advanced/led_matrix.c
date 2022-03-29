#include "pico/stdlib.h"
#include "led_matrix.h"
#include "hardware/uart.h"

#define UART_ID uart1
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY    UART_PARITY_NONE

// We are using pins 0 and 1, but see the GPIO function select table in the
// datasheet for information on which other pins can be used.
#define UART_TX_PIN 4
#define UART_RX_PIN 5


uint32_t image[ROWS_IMAGE][COLUMNS_IMAGE];
uint32_t flattened_data[ROWS_IMAGE * COLUMNS_IMAGE];
extern uint8_t buffered_chars[3072];


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

void image_from_uart()
{
    static bool initialized = false;

        // Set up our UART with the required speed.
    if(!initialized){
        
        uart_init(UART_ID, BAUD_RATE);

        // Set the TX and RX pins by using the function select on the GPIO
        // Set datasheet for more information on function select
        gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

        // Turn off FIFO's - we want to do this character by character
        // uart fifo is 16 bytes deep
        uart_set_fifo_enabled(UART_ID, false);

        initialized = true;
    }
    static Colour pixel;
    static uint8_t read_buffer[ROWS_IMAGE * COLUMNS_IMAGE * 3];
    uart_read_blocking(UART_ID, read_buffer, sizeof(read_buffer) - 1);

    int j = 0;
    int k = 0;

    for(int i = 0; i < sizeof(read_buffer); i+=3)
    {
        pixel.red = read_buffer[i];
        pixel.green = read_buffer[i + 1];
        pixel.blue = read_buffer[i + 2];

        image[j][k] =  (uint32_t)((pixel.green) << 16) |
                        (uint32_t)((pixel.red) << 8) |
                        (uint32_t)((pixel.blue));

        j++;

        if((j % ROWS_IMAGE) == 0){
            k++;
        }


    }
           
    
}


void init_test_image()
{
    uint32_t pixel = 0xffffff;

    for(int i = 0; i < ROWS_IMAGE; i++)
    {
        for(int j = 0; j < COLUMNS_IMAGE; j++)
        {
            image[i][j] = pixel >> (j * 2);
        }
    }
}

void squares_image()
{
    static Square square_one = {32, 5, {0,0}, RED};

    for(int i = 0; i < ROWS_IMAGE; i++)
    {
        for(int j = 0; j < COLUMNS_IMAGE; j++)
        {
            if(((i >= square_one.origin.x) &&  \
            (i <= (square_one.origin.x + square_one.width))) &&  \
            ((j >= square_one.origin.y) && \
            (j <= (square_one.origin.y + square_one.height))))
            {
                image[i][j] = 0xffffff;
            } else {
                image[i][j] = 0;
            }
        }
    }
}


void process_read_buffer() 
{
    Colour pixel;

    int i = 0;
    char str[20];
    char str2[20];

    for(int k = 0; k < ROWS_IMAGE; k++)
    {
        for(int j = 0; j < COLUMNS_IMAGE; j++)
        {
            sprintf(str, "k %d, j %d : R %d G %d B %d ", k, j, buffered_chars[i], buffered_chars[i + 1], buffered_chars[i + 2]);
            uart_puts(UART_ID, str);
            pixel.red = buffered_chars[i++];
            pixel.green = buffered_chars[i++];
            pixel.blue = buffered_chars[i++];

            image[j][k] =  (uint32_t)((pixel.green) << 16) |
                            (uint32_t)((pixel.red) << 8) |
                            (uint32_t)((pixel.blue));

            sprintf(str2, "pix = %d\n", image[j][k]);
            uart_puts(UART_ID, str2);
        }
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


void prepare_data_for_panel2(int panel_no)
{
    bool flip_row = true;

    int col_offset = (COLUMNS_PANEL * panel_no);
    int offset = COLUMNS_PANEL * ROWS_PANEL * panel_no;

    for (int i = 0; i < ROWS_PANEL; i++)
    {
        flip_row = !flip_row;

        if(flip_row)
        {   
            for(int j = 0; j < COLUMNS_PANEL; j++)
            {
                flattened_data[(i * (COLUMNS_PANEL) + ((COLUMNS_PANEL - 1) - j) + offset)] = image[i][j + col_offset];
            }
            
        } else {
            for(int j = 0; j < COLUMNS_PANEL; j++)
            {
                flattened_data[(i * COLUMNS_PANEL) + j + offset] = image[i][j + col_offset];
            }

        }

    }
}



void test_image_vertical()
{
    static Colour start = RED;
    static Colour middle = BLUE;
    static Colour finish = GREEN;

    static uint8_t start_row = 0;
    static uint8_t finish_row = 23;

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
        prepare_data_for_panel2(i);
    }
}