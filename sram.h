#pragma once
#define external_mem_baseadress 0x1800

#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"

void xmem_init(void);
void SRAM_test(void);

void xmem_write(uint8_t data, uint16_t addr);

uint8_t xmem_read(uint16_t addr);