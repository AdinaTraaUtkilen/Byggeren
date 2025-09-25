#pragma once

#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"
#include "sram.h"
#include "adc.h"


void test_uart();

void manual_latch_test();

void sram_test_func();

void position_test(jx,jy,tx,ty,pos,d);