
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

#define BAUD 9600
#define MYUBRR F_CPU / 16 / BAUD - 1


volatile uint8_t jx = 0, jy = 0, tx = 0, ty = 0;
volatile pos_t   pos = {0};
volatile dir     d   = NEUTRAL;
volatile uint8_t control_flag = 0;



int main()
{
  USART_Init(MYUBRR);
  xmem_init();
  adc_init();
  init_interrupt();
  spi_master_init();

 

 while (1)
 { 
   adc_read_init();
    if(control_flag){
      control_flag = 0; // clear flagg
    }

    position_test(&jx, &jy, &tx, &ty, &pos, &d);
/*
    spi_activate_disp_cs();
    spi_master_transmit(0xAA); //dummy
    _delay_ms(200);

    volatile uint8_t trash; // nullstille flagget
    trash = SPSR;
    trash = SPDR;
    */


  _delay_ms(1000);

 }

  return 0;
};
