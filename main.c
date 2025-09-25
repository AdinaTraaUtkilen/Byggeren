
#define F_CPU 4915200UL

#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "spi.h"

#define BAUD 9600
#define MYUBRR F_CPU / 16 / BAUD - 1

int main()
{
  USART_Init(MYUBRR);
  xmem_init();
  adc_init();
  spi_master_init();
 
  pos_t pos;
  uint8_t jx, jy, tx, ty;
  dir d = NEUTRAL;  

 

 while (1)
 { 

    spi_activate_disp_cs();



  
  _delay_ms(1000);

 }

  return 0;
};
