#pragma once

#include <stdint.h>

typedef enum { LEFT, RIGHT, UP, DOWN, NEUTRAL } dir;

typedef struct {
    int8_t joystick_x;
    int8_t joystick_y;
    int8_t touchpad_x;
    int8_t touchpad_y;
    int8_t btn_pressed;
} pos_t;

extern volatile pos_t pos;

typedef enum { PLAY_A, SCOREBOARD_A } homescreen_arrow;
typedef enum { HOME, PLAY, SCOREBOARD} pages;


extern volatile uint8_t jx, jy, tx, ty;

extern volatile dir d;
extern volatile uint8_t control_flag;
extern volatile homescreen_arrow arrow;
extern volatile pages page;