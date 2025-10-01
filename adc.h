#pragma once
#define adc_baseadress 0x1400

#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"
#include "global.h"


void adc_init(void);
void adc_read_init();
void adc_read(uint8_t* jx, uint8_t* jy, uint8_t* tx, uint8_t* ty);

void pos_calibrate(uint8_t* jx, uint8_t* jy, uint8_t* tx, uint8_t* ty, pos_t *pos);
 
void pos_read(pos_t *pos, dir* d);

void pos_direction(pos_t *pos, dir *d);

