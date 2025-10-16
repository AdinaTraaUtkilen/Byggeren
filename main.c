
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
  mcp2515_init();
  can_init();
  can_message m = {.id=0x123, .length = 3, .data={0x11,0x22,0x33}};


 while (1)
 {  
 // menu_test(&jx, &jy,&tx, &ty, &pos, &d, &btn, &page, &arrow);
  //bit_modify_test();
  
  can_message_send(&m);
  for (int i=0;i<50;i++){
        can_message rx;
        if (can_message_receive(&rx)) {
            printf("RX id=0x%03X len=%d data:", rx.id, rx.length);
            for (int k=0;k<rx.length;k++) printf(" %02X", (uint8_t)rx.data[k]);
            printf("\r\n");
            break;
        }
        _delay_ms(2);
    }

    _delay_ms(500);
 
 };

  return 0;
};
