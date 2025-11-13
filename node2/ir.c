#include "ir.h"

float alpha = 0.1f; //alpha = 1 raverdi, alpha = 0, dempet
float ir_filtered_signal = 0.0f;
uint8_t score = 0;
uint8_t passed = 0;
uint8_t last_passed = 0;

void ir_init(){
    // AD0 adc analog input 
    // power managment controller må styre klokke
    PMC -> PMC_PCER1 = PMC_PCER1_PID37; //klokke for adc

    //normal mode by default?
    ADC -> ADC_MR = ADC_MR_PRESCAL(41) | ADC_MR_STARTUP_SUT64 | ADC_MR_TRANSFER(1) | ADC_MR_TRACKTIM(3); // tabell 45-30, ØNSKER 1 MHz trenger vi flere?
    ADC -> ADC_CHER = ADC_CHER_CH7;


}
uint16_t ir_read(){
    ADC-> ADC_CR = ADC_CR_START; // start konvertering
    uint32_t guard = 1000000; 
    while(!(ADC->ADC_ISR & ADC_ISR_EOC7)){
        if(--guard == 0) return 0;
    }; // venter til EOC0 = 1, ferdig konverteirng, polling - leser statusregisteeer
    uint16_t ir_signal = ADC-> ADC_CDR[7];
    return ir_signal;
    //ir_filter_signal(ir_signal);
    
}

//ema filter digitalt lavpass som glatter ut
float ir_filter_signal(uint16_t ir_signal){
 
    ir_filtered_signal = ((1 - alpha)*ir_filtered_signal) + (alpha * ir_signal);
    float ir_filtered_volt =  ir_filtered_signal * 3.3f / 4095.0f;
    return ir_filtered_volt;


}

uint8_t update_game(float ir_signal){
    if (ir_signal < 0.60f){
        passed = 1;
        if (passed && last_passed == 0)
        {
            score = score + 1;
            last_passed = 1;
        }
        return score;
    } else {
        passed = 0;
        last_passed = 0;
        return score;
    }
   
}





