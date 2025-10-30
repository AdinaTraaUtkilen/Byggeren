#pragma once
#include "sam/sam3x/include/sam3x8e.h"
#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/include/component/component_pwm.h"
#include "startcode/can.h"

void pwm_driver();

void servo_driver();


void check_min_max(uint16_t reg_duty_cycle);


void joystick_to_pwm(CanMsg* message);