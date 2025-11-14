#pragma once
#define F_CPU 4915200UL



#include "avr/io.h"
#include "util/delay.h"
#include <stdlib.h>
#include "spi.h"
#include "global.h"
#include "avr.h"


void oled_init();

void oled_print_arrow (uint8_t page, uint8_t column );

void oled_write_data(char data);

void oled_write_command(char data);

void oled_home();

void oled_goto_page(uint8_t page);


void oled_goto_column(uint8_t column);


void oled_clear_page(uint8_t page);

void oled_clear_all();

void oled_pos(uint8_t row, uint8_t column);

void oled_print_char(char c,uint8_t page,  uint8_t column, uint8_t font);

void oled_print_str(const char *str,uint8_t page, uint8_t column, uint8_t font);

uint8_t font_index(char c);


void change_page(volatile pages* page,volatile homescreen_arrow* arrow, volatile Buttons *btn);

void oled_change_arrow(volatile dir* d,  volatile homescreen_arrow* arrow);


void home_button(volatile Buttons *btn, volatile pages *page, volatile homescreen_arrow* arrow);

void led_play();
void led_scoreboard();

void oled_update_score(uint8_t score);

/*




//void oled_set_brightness(uint8_t lvl);
*/