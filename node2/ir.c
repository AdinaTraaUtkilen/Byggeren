#include "ir.h"

void ir_init(){
    // AD0 adc analog input 
    // power managment controller må styre klokke
    PMC -> PMC_PCER1 = PMC_PCER1_PID37; //klokke for adc

    //normal mode by default?
    ADC -> ADC_MR = ADC_MR_PRESCAL(41); // tabell 45-30, ØNSKER 1 MHz trenger vi flere?
    ADC -> ADC_CHER = ADC_CHER_CH0;


}

uint8_t ir_read(){
    ADC-> ADC_CR = ADC_CR_START; // start konvertering
    while(!(ADC->ADC_ISR & ADC_ISR_EOC0)); // venter til EOC0 = 1, ferdig konverteirng, polling - leser statusregisteeer
    uint8_t ir_signal = ADC-> ADC_CDR[0];
    uint8_t ir_signal_filtered;
    return ir_signal;
    
}


void count_score(uint8_t ir_signal){
    uint8_t score = 0;


}