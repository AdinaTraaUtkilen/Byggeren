
#define F_CPU 4915200UL

#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"
#include "uart.h"
#include "sram.h"

#define BAUD 9600
#define MYUBRR F_CPU / 16 / BAUD - 1

int main()
{
  USART_Init(MYUBRR);

  // manuell latch test, styrer pinnene direkte utifra høy/ lav latch oving 2

  // setter som output
  // DDRD |= (1 << PD2);
  // DDRE |= (1 << PE1); // PE til LE, latch enable PE1 = ALE!!!
  // DDRA |= 0xFF;         // pa0 til pa7 til latch

  // PORTE &= ~(1 << PE1); // holde le lav, holder Q

  // PORTA = 0b01010101;
  // PORTE |= (1 << PE1);  // LE høy, sende gjennom
  // PORTE &= ~(1 << PE1); // Le lav, låse verdien

  // PORTA = 0b10101010; // D endres, Q uendret

  // ekstern minne tar over

  xmem_init();
  SRAM_test();

  // toggle oving 1 - uart
  // while (1)
  // {
  // ext_mem[1200] = 0x55; // 0101 0101,
  // _delay_ms(1500);

  //  PORTD ^= (1 << PD2);

  // unsigned char c = USART_Receive();
  // USART_Transmit(c);

  // printf("Test");
  //};

  return 0;
};
