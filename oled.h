#pragma once

#include "avr/io.h"
#include "util/delay.h"
#include <stdlib.h>
#include "spi.h"


void oled_init();

void oled_print_arrow ();

void oled_write_data(char data);

void oled_write_command(char data);

void oled_home();

void oled_goto_page(uint8_t page);


void oled_goto_column(uint8_t column);


void oled_clear_page(uint8_t page);

void oled_clear_all();

/*
void oled_pos(uint8_t row, uint8_t column);


void oled_print(char*);

//void oled_set_brightness(uint8_t lvl);
*/