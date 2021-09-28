#include "pico/stdlib.h"
#include "led_matrix.h"
#include "numbers.h"
#include <string.h>

// width and height of runes
#define WIDTH 6
#define HEIGHT 5

// define number positions here
#define POSITION_0 1
#define POSITION_1 6
#define POSITION_2 11
#define POSITION_3 16
#define POSITION_4 21
#define POSITION_5 27

//void *memcpy(void *dest, const void * src, size_t n)

uint32_t block[HEIGHT][WIDTH] = {{0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff},{0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff},{0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff},{0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff},{0xffffff,0xffffff,0xffffff,0xffffff,0xffffff,0xffffff}};

// copy rune into image array at defined offset 
void insert_number(int position)
{
    for(int i = 0; i < HEIGHT; i++)
    {
        memcpy(image[i], block[i], 6*sizeof(uint32_t));
    }
}