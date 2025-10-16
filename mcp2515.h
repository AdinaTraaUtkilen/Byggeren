#pragma once


#include "avr/io.h"
#include "spi.h"

void mcp2515_init();

void mcp2515_reset();

uint8_t mcp2515_read(uint8_t address);

void mcp2515_write(uint8_t address, uint8_t data);

uint8_t read_status();

void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t new_data);

void mcp2515_request_to_send(uint8_t buffer);