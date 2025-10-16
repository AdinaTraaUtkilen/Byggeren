#pragma once

#include "avr/io.h"


typedef struct {
    uint16_t id;
    uint8_t length;
    uint8_t data[8];
} can_message;

void can_init();

void can_message_send();

void can_message_receive();

void can_transmit_complete();