#pragma once

#include <stdint.h>

typedef enum { LEFT, RIGHT, UP, DOWN, NEUTRAL } dir;

typedef struct {
    int8_t joystick_x;
    int8_t joystick_y;
    int8_t touchpad_x;
    int8_t touchpad_y;
} pos_t;

extern volatile uint8_t jx, jy, tx, ty;
extern volatile pos_t pos;
extern volatile dir d;
extern volatile uint8_t control_flag;

const char *dir_str(dir d);
