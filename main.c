
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


  // adc og joystick oving 3 - oppg. 3

 adc_init();
  pos_t pos;
  uint8_t jx, jy, tx, ty;
  dir d = NEUTRAL;


 while (1)
 {
  
  adc_read(&jx, &jy, &tx, &ty);
  pos_calibrate(&jx, &jy, &tx, &ty, &pos);
  pos_read(pos);
  
  pos_direction(&pos, &d);


  printf("direction joystick %s \r\n", dir_str(d));
  _delay_ms(1000);

 }

  return 0;
};
