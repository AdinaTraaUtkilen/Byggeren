
#define F_CPU 4915200UL

#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "spi.h"
#include "oled.h"
#include "interrupt.h"
#include "global.h"
#include "avr.h"
#include "labtester.h"
#include "mcp2515.h"
#include "can.h"

#define BAUD 9600
#define MYUBRR F_CPU / 16 / BAUD - 1


volatile uint8_t jx = 0, jy = 0, tx = 0, ty = 0, bp = 0;
volatile pos_t pos;
volatile dir d = NEUTRAL;
volatile uint8_t control_flag = 0;
volatile Buttons btn;
volatile homescreen_arrow arrow = PLAY_A;
volatile pages page = HOME;




int main()
{
  USART_Init(MYUBRR);
  xmem_init();
  adc_init();
  init_interrupt();
  spi_master_init();
  led_init(); 
  oled_init();
  oled_home();
  mcp2515_init();
  can_init();
  can_message m = {0x23, 5, {0}};


  adc_read(&jx, &jy,&tx, &ty);
  if(control_flag){
      control_flag = 0; // clear flagg
    }


 while (1)
 {  
  menu_test(&jx, &jy,&tx, &ty, &pos, &d, &btn, &page, &arrow);
 
 
  send_joystick_pos(&m);
 // _delay_ms(200);
 
 }
  return 0;
};



 /*
  
 */