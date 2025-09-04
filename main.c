
//#define F_CPU 4915200UL

#include "util/delay.h"
#include "avr/io.h"

#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1



int main() {

    //output
    DDRD |= (1 << PD2);

    USART_Init ( MYUBRR );
    
    while(1) {

        USART_Transmit('a' );
        
         _delay_ms(2000);

        // toggle
        //PORTD ^= (1 << PD2);

    
        unsigned char c = USART_Receive();
          
       };
       

    return 0;
};

