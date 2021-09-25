

#include "led_ring_dots.h"


const float leds_per_radian = NUMBER_OF_LEDS / 6.242;

int positions[NUMBER_OF_LEDS];

void calculate_speed(Dot* dots, int loop_time_ms) {

    for(int i = 0; i < NUMBER_OF_DOTS; i++){
        dots[i].speed_rad_s += (dots[i].angular_acc * ((float)loop_time_ms / 1000));
    }

}

void calculate_angle(Dot* dots, int loop_time_ms) {

    for(int i = 0; i < NUMBER_OF_DOTS; i++){
        dots[i].theta += dots[i].speed_rad_s * ((float)loop_time_ms / 1000);
    }

}

void check_end_stop(Dot* dots) {
    for(int i = 0; i < NUMBER_OF_DOTS; i++) {
        if(dots[i].theta > 6.242) {
            dots[i].theta = 0;
            dots[i].speed_rad_s = 0;
        }

    }
}

void update_colours(Dot* dots) {

    static bool go_red = false;

    if(!go_red){
        for(int i = 0; i < NUMBER_OF_DOTS; i++) {
            if((dots[i].animation.current_colour.red > 0) && (dots[i].animation.current_colour.blue < 255)) {
                dots[i].animation.current_colour.red--;
                dots[i].animation.current_colour.blue++;
            } else {
                go_red = true;
                break;
            }
        }
    } else {
        for(int i = 0; i < NUMBER_OF_DOTS; i++) {
            if((dots[i].animation.current_colour.blue > 0) && (dots[i].animation.current_colour.red < 255)) {
                dots[i].animation.current_colour.red++;
                dots[i].animation.current_colour.blue--;
            } else {
                go_red = false;
                break;
            }
        }
    }
}


void calculate_led(Dot* dots) {
    for(int i = 0; i < NUMBER_OF_DOTS; i++) {
        dots[i].led = (int)(dots[i].theta * leds_per_radian);       
    }
}