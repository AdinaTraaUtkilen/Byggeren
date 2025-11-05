#pragma once


#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/include/component/component_adc.h"
#include "startcode/time.h"

void ir_init();

uint16_t ir_read();

float ir_filter_signal(uint16_t ir_signal);


uint8_t update_game(float ir_signal);


void start_game();