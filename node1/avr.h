#pragma once

#define F_CPU 4915200UL

#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"
#include "spi.h"
#include "global.h"

 // Buttons and led */

typedef struct __attribute__((packed)) {
    union {
        uint8_t right;
        struct {
            uint8_t R1:1;
            uint8_t R2:1;
            uint8_t R3:1;
            uint8_t R4:1;
            uint8_t R5:1;
            uint8_t R6:1;
            };
            };

    union {
        int8_t left;
        struct {
            uint8_t L1:1;
            uint8_t L2:1;
            uint8_t L3:1;
            uint8_t L4:1;
            uint8_t L5:1;
            uint8_t L6:1;
            uint8_t L7:1;
            };
        };

    union {
        uint8_t nav;
        struct {
            uint8_t NB:1;
            uint8_t NR:1;
            uint8_t ND:1;
            uint8_t NL:1;
            uint8_t NU:1;
            };
    };
} Buttons;



void leds_change_state(uint8_t command, uint8_t led_num);

void led_on(uint8_t led_num);
void led_off(uint8_t led_num);

void led_init();

void read_joystick_button(volatile pos_t *pos);


void update_buttons(volatile Buttons *btn);
