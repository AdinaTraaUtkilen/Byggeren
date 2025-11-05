#pragma once


#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/include/component/component_adc.h"

void ir_init();

uint8_t ir_read();

void count_score(uint8_t ir_signal);