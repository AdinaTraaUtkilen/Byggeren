
#define F_CPU 4915200UL

#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"
#include "uart.h"
#include "sram.h"
#include "adc.h"

#define BAUD 9600
#define MYUBRR F_CPU / 16 / BAUD - 1

int main()
{
  USART_Init(MYUBRR);
  xmem_init();
//  SRAM_test();

  // adc og joystick oving 3 - oppg. 3

 adc_init();
 while (1)
 {
   
    printf("Lese verdi: %d\n", adc_read());
    _delay_ms(500);


 }
 

  


  return 0;
};

void ex1_toggle();