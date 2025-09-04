#define F_CPU 4915200UL
#include "util/delay.h"
#include "avr/io.h"




int main() {

    //input
    DDRC |= (1 << PC6);

    while(1) {
        // toggle
        PORTC ^= (1 << PC6);


        _delay_ms(200);

    };

    return 0;
};