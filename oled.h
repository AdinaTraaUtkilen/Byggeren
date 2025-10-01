#pragma once

#include "avr/io.h"
#include "util/delay.h"
#include <stdlib.h>


void oled_init();


void oled_reset();

void oled_home();

void oled_goto_line();

void oled_clear_line();
