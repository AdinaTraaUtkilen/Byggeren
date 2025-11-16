#pragma once

#include "sam/sam3x/include/sam.h"
#include "sam/sam3x/include/component/component_tc.h"
#include "startcode/can.h"
#include "math.h"
#include "servo.h"





void pwm_motor_driver();

void encoder_driver_init();

uint32_t read_encoder();

void joystick_to_pwm_motor(CanMsg* message);

void position_controller(uint32_t encoder_value, CanMsg* message);

uint32_t encoder_pos_func(int32_t encoder_value);

void pi_motor_set_cdty(float u);