#pragma once

#include "avr/io.h"
#include "avr.h"
#include "mcp2515.h"
#include <stdbool.h>


typedef struct {
    uint16_t id;
    char length;
    char data[8];
} can_message;

void can_init();

void can_message_send(can_message *message);

bool can_message_receive(can_message *m_out);

void can_transmit_complete();