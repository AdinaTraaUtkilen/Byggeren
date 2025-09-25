#include <stdlib.h>
#include "adc.h"

volatile uint8_t *ADC_BASE = (uint8_t*)0x1400; //baseadresse ADC

void adc_init(void){
    MCUCR |= (1 << SRE); // enable external memory (XMEM)

    SFIOR |= (1 << XMM2); // masking out pins used for jtag PC4 - PC7

    // klokke output OC1A 
    DDRD |= (1 << PD5);

    TCCR1A = (1 << WGM11) | (1 << WGM10) | (1 << COM1A0); // toggle OC1A på compare
    TCCR1B = (1 << WGM13) | (1<< WGM12)| (1 << CS10); // CTC, prescaler = 1, F-cpu = 4.9 Mhz
    OCR1A = 2; // 0,1,2,3 fungerer i område

   // 0.8192 mHz Mhz: 4.9 / 2*1 + (1+2)

    // min 0.5 mhz og maks 5mhz
    DDRD &= ~(1 << PD2); // PD2 som inngang for busy, sjekke når den blir aktiv høy


}


volatile uint8_t adc_read(){
    ADC_BASE[0] = 0; //cs og write lav
    
   while(!(PIND & (1 << PD2))){ //vente til busy ferdig. page 15 in adc datasheet
    ;
   };
   

  // _delay_ms(200);


    volatile uint16_t value_x = ADC_BASE[0]; // leser fra adc med 4 channels
    volatile uint16_t value_y = ADC_BASE[0];
    volatile uint16_t value3 = ADC_BASE[0];
    volatile uint16_t value4 = ADC_BASE[0];
    return value_x;
    
}

void pos_calibrate(){

}


pos_t pos_read(void);


