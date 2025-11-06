#pragma once


#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/include/component/component_tc.h"


void pwm_encoder_driver();

void encoder_driver();

uint32_t read_encoder();

void motor_driver();


