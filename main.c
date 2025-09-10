
#define F_CPU 4915200UL
#define external_mem_baseadress 0x1800


#include "avr/io.h"
#include "util/delay.h"
#include "uart.h"
#include "stdio.h"



#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1




int main() {

    //output
    DDRD |= (1 << PD2);
    DDRE |= (1 << PE1);

    USART_Init ( MYUBRR );

    MCUCR |= (1 << SRE);

    volatile uint8_t *ext_mem = (uint8_t *) external_mem_baseadress;
    PORTE = 0b10; //
    PORTA = 0x55;

    
    while(1) {
        
        //*ext_mem = 0x55; // 0101 0101
      
        

       // *(ext_mem + 1) = 0xAA; // 1010 1010
       // _delay_ms(500);


        // toggle
      //  PORTD ^= (1 << PD2);

    
       // unsigned char c = USART_Receive();
       // USART_Transmit(c);

     //   printf("Test");

        

        

          
       };
       

    return 0;
};

