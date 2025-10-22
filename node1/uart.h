#pragma once
#include <stdint.h>


void USART_Init( unsigned int ubrr );
void USART_Transmit( char data );

char USART_Receive( void );

