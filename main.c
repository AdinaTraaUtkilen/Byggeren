
#define F_CPU 4915200UL
#include "avr/io.h"
#include "util/delay.h"
#include "uart.h"
#include "stdio.h"



#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1



int main() {

    //output
    DDRD |= (1 << PD2);

    USART_Init ( MYUBRR );

    
    while(1) {

      
        _delay_ms(1000);

        // toggle
        PORTD ^= (1 << PD2);

    
       // unsigned char c = USART_Receive();
       // USART_Transmit(c);

        printf("Test");

          
       };
       

    return 0;
};

