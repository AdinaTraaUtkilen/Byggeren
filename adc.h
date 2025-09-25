#pragma once
#define adc_baseadress 0x1400

#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"

typedef struct {
    int8_t joystick_x;
    int8_t joystick_y;
    int8_t touchpad_x;
    int8_t touchpad_y;
} pos_t;

typedef enum {LEFT, RIGHT, UP, DOWN, NEUTRAL} dir;

void adc_init(void);
void adc_read(uint8_t* jx, uint8_t* jy, uint8_t* tx, uint8_t* ty);

void pos_calibrate(uint8_t* jx, uint8_t* jy, uint8_t* tx, uint8_t* ty, pos_t *pos);
 
void pos_read(pos_t pos);

void pos_direction(pos_t *pos, dir *d);


char *dir_str(dir d);