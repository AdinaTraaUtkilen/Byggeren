#pragma once
#define adc_baseadress 0x1400

#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"

typedef struct {
    int8_t x;
    int8_t y;
} pos_t;

void adc_init(void);

volatile uint8_t adc_read(uint8_t channel);

void pos_calibrate();
 
pos_t pos_read(void);
