#pragma once


#include "avr/io.h"
#include "util/delay.h"
#include <stdlib.h>


void spi_master_init();


void spi_slave_init();

void spi_master_transmit(char cData);

char spi_slave_receive(void);

void spi_activate_disp_cs();
void spi_activate_io_cs();

void spi_deactivate_all(void);