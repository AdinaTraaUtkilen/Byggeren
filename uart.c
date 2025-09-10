#include "uart.h"
#include <stdio.h>
#include <avr/io.h>

// alt hentet fra datablad ATmega162 side 172-


void USART_Init( unsigned int ubrr )
{
    /* Set baud rate */
    UBRR0H = (unsigned char)(ubrr>>8);
    UBRR0L = (unsigned char)ubrr;
    /* E0nable receiver and transmitter */
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    /* S0et frame format: 8data, 2stop bit */
   UCSR0C = (1<<URSEL0)|(1<<USBS0)|(3<<UCSZ00);


    fdevopen(USART_Transmit, USART_Receive);
}



void USART_Transmit( char data )
{
/* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );
/* Put data into buffer, sends the data */
    UDR0 = data;
}


char USART_Receive( void )
{
/* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) );
/* Get and return received data from buffer */
    return UDR0;
}

