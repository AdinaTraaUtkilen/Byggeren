#include "spi.h"

/*Atmel 162 page 160 */

void spi_master_init(){
    /*Set MOSI and SCK output, all others input*/
    DDRB |= (1 << DDB5) | (1 << DDB7);
    DDRB |= (1 << PB4);   // SS som utgang
    PORTB |= (1 << PB4);  // og høy

    /*Enable SPI, master, set clock rate fck/16 */
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);

    DDRD |= (1 << PD3); // CS_disp som utgang - retning
    DDRD |= (1 << PD4); // CS_io som utgang - retning

    PORTD |= (1 << PD4); // setter pinen høy
    PORTD |= (1 << PD3); // setter pinen høy
}


void spi_slave_init(){
    /*Set MOSI til output, all others input*/
    DDRB = (1 << DDB5);

    /*Enable SPI */
    SPCR = (1 << SPE);

  
}

void spi_master_transmit(char cData){
    /*Start transmission*/
    SPDR = cData;

    /*Wait for transmission complete*/
    while(!(SPSR & (1<<SPIF))){
        (void)SPDR;
    };

}



char spi_slave_receive(void){
    /*Wait for reception complete */
    while(!(SPSR & (1 << SPIF)));

    /*Return data register*/
    return SPDR;
}



void spi_activate_disp_cs(){
    PORTD &= ~(1 << PD3);
    PORTD |= (1 << PD4); // setter pinen høy

}

void spi_activate_io_cs(){
    PORTD &= ~(1 << PD4); // aktivere io ved å sette lav
    PORTD |= (1 << PD3); // deaktiverer disp

}

void spi_deactivate_all(void){
    PORTD |= (1 << PD3);
    PORTD |= (1 << PD4);
}
