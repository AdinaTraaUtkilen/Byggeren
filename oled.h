#pragma once

#include "avr/io.h"
#include "util/delay.h"
#include <stdlib.h>
#include "spi.h"


void oled_init();

void oled_print_arrow ();

void oled_write_data(char data);

void oled_write_command(char data);

void oled_reset();

void oled_home();

void oled_goto_line(line);


void oled_goto_column(column);


void oled_clear_line(line);

void oled_pos(row, column);


void oled_print(char*);

void oled_set_brightness(lvl);
