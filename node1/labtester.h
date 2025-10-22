#pragma once
#define F_CPU 4915200UL


#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"
#include "sram.h"
#include "adc.h"
#include "global.h"
#include "avr.h"
#include "oled.h"
#include "mcp2515.h"


void test_uart();

void manual_latch_test();

void sram_test_func();

void position_test(uint8_t *jx,uint8_t *jy,uint8_t *tx,uint8_t *ty,pos_t *pos,dir *d, volatile uint8_t *control_flag);


void spi_test();

void led_test();

void menu_test(uint8_t *jx,uint8_t *jy,uint8_t *tx,uint8_t *ty, volatile pos_t *pos, volatile dir *d, volatile Buttons *btn, volatile pages *page, volatile homescreen_arrow *arrow);

void bit_modify_test();