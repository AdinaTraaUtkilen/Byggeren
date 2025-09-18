#include <stdlib.h>
#include "adc.h"

void adc_init(void){
    MCUCR |= (1 << SRE); // enable external memory (XMEM)

    SFIOR |= (1 << XMM2); // masking out pins used for jtag PC4 - PC7

    // klokke output OC1A 
    DDRD |= (1 << PD5);

    TCCR1A = (1 << WGM11) | (1 << WGM10); // toggle OC1A på compare
    TCCR1B = (1 << WGM13) | (1<< WGM12) | (1 << CS10); // CTC, prescaler = 1, F-cpu = 4.9 Mhz
   // 0.8192 mHz Mhz: 4.9 / 2*1 + (1+2)

    // min 0.5 min hz og maks 5mhz
}


volatile uint8_t adc_read(uint8_t channel){
    

}

void pos_calibrate(){

}


pos_t pos_read(void);


