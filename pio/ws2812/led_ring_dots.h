
#include "pico/stdlib.h"

#define NUMBER_OF_LEDS 24
#define NUMBER_OF_DOTS 4
#define RED     {255,0,0}
#define BLUE   {0,255,0}
#define GREEN    {0,0,255}

const float leds_per_radian;

typedef struct {
        uint8_t red;
        uint8_t blue;
        uint8_t green;
} Colour;

typedef struct {
        Colour current_colour;
        Colour target_colour;
        Colour start_colour;
        uint8_t increment;
} Animation;

typedef struct {
        float theta;
        float speed_rad_s;
        int angular_acc;
        int led;
        Animation animation;
} Dot;

void calculate_speed(Dot* dots, int loop_time_ms);
void calculate_angle(Dot* dots, int loop_time_ms);
void check_end_stop(Dot* dots);
void calculate_led(Dot* dots);
void update_colours(Dot* dots);