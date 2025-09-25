#include <stdlib.h>
#include "labtester.h"



  //   ---------------------- oving 1 -----------------------------------
void test_uart(){
  volatile uint32_t *ext_mem = (volatile uint32_t*) external_mem_baseadress;
  ext_mem[1200] = 0x55; // 0101 0101,
  _delay_ms(1500);

  PORTD ^= (1 << PD2);

  unsigned char c = USART_Receive();
  USART_Transmit(c);

  printf("Test");

}


  //   ---------------------- oving 2 - oppg.1 -----------------------------------
void manual_latch_test(){ // styrer pinene direkte utifra høy/lav latch
   // setter som output

  DDRD |= (1 << PD2);
  DDRE |= (1 << PE1); // PE til LE, latch enable PE1 = ALE!!!
  DDRA |= 0xFF;         // pa0 til pa7 til latch

  PORTE &= ~(1 << PE1); // holde le lav, holder Q

  PORTA = 0b01010101;
  PORTE |= (1 << PE1);  // LE høy, sende gjennom
  PORTE &= ~(1 << PE1); // Le lav, låse verdien

  PORTA = 0b10101010; // D endres, Q uendret

}



// --------------------------  oving 2 - oppg. 2 & 4---------------------------------------
void sram_test_func(){ // ekstern minne tar over 

  SRAM_test();
  volatile uint8_t *ADC_REG = (uint8_t*)0x1400; // peker til adc, hvor a11 er 0
  volatile uint8_t *SRAM_REG = (uint8_t*)0x1800; // peker til stram, hvor a11 er 1, og blir invertert i nand

}



// --------------------------  oving 3---------------------------------------
void position_test(jx, jy, tx, ty, pos,d){ 

  /*Inni while*/
  adc_read(&jx, &jy, &tx, &ty);
  pos_calibrate(&jx, &jy, &tx, &ty, &pos);
  pos_direction(&pos, &d);

  pos_read(pos, &d);
  
}
















