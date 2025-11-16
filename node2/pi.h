#pragma once

#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/include/component/component_tc.h"
#include "sam/sam3x/include/instance/instance_tc0.h"
#include "sam/interrupt.h"
#include "startcode/can.h"
#include "motordriver.h"
#include "stdint.h"



void position_controller(uint32_t encoder_value, CanMsg* message);

void pid_timer_init();

void TC0_Handler();

void position_controller(uint32_t encoder_pos, CanMsg* message);

