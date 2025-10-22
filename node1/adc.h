#pragma once
#define adc_baseadress 0x1400

#include "avr/io.h"
#include "stdio.h"
#include "global.h"


void adc_init(void);
void adc_read_init();
void adc_read(volatile uint8_t* jx,volatile uint8_t* jy,volatile uint8_t* tx,volatile uint8_t* ty);

void pos_calibrate(volatile uint8_t* jx,volatile uint8_t* jy,volatile uint8_t* tx,volatile uint8_t* ty, volatile pos_t *pos);
 
void pos_read(volatile pos_t *pos,  volatile dir*d);

void pos_direction(volatile pos_t *pos, dir volatile *d);


const char *dir_str(dir d);

void position_update(uint8_t volatile *jx,uint8_t volatile *jy,uint8_t volatile  *tx,uint8_t  volatile *ty,pos_t volatile *pos, dir volatile *d);