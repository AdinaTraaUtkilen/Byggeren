
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

#define BAUD 9600
#define MYUBRR F_CPU / 16 / BAUD - 1


volatile uint8_t jx = 0, jy = 0, tx = 0, ty = 0;
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

 while (1)
 {  
  position_update(&jx,&jy,&tx,&ty,&pos, &d);
  read_joystick_button(&pos);
  update_buttons(&btn);
  
 
  if(page == HOME){
      oled_change_arrow(&d, &arrow);
  }

  if (pos.btn_pressed == 1){
    printf("der trykket jeg");
    change_page(&page, &arrow, &btn);
  }
  home_button(&btn, &page,&arrow);
 


  _delay_ms(100);
  


 };

  return 0;
};
