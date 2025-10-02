#pragma once

#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"
#include "sram.h"
#include "adc.h"
#include "global.h"
#include "avr.h"


void test_uart();

void manual_latch_test();

void sram_test_func();

void position_test(uint8_t *jx,uint8_t *jy,uint8_t *tx,uint8_t *ty,pos_t *pos,dir *d);


void spi_test();

void led_test();