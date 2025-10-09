#pragma once

#include <stdint.h>

typedef enum { LEFT, RIGHT, UP, DOWN, NEUTRAL } dir;
typedef enum { PLAY, SCOREBOARD } homescreen_menu;
typedef struct {
    int8_t joystick_x;
    int8_t joystick_y;
    int8_t touchpad_x;
    int8_t touchpad_y;
    int8_t btn_pressed;
} pos_t;

extern volatile uint8_t jx, jy, tx, ty;
extern volatile pos_t pos;
extern volatile dir d;
extern volatile uint8_t control_flag;

