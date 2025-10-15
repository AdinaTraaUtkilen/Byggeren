#pragma once

#include <stdint.h>

typedef enum { LEFT, RIGHT, UP, DOWN, NEUTRAL } dir;
typedef enum { PLAY_A, SCOREBOARD_A } homescreen_arrow;
typedef enum { HOME, PLAY, SCOREBOARD} pages;


typedef struct {
    int8_t joystick_x;
    int8_t joystick_y;
    int8_t touchpad_x;
    int8_t touchpad_y;
    int8_t btn_pressed;
} pos_t;




