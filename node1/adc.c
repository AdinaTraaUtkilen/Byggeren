#include <stdlib.h>
#include "adc.h"

volatile uint8_t *ADC_BASE = (volatile uint8_t*)0x1400; //baseadresse ADC

void adc_init(void){
    // klokke output OC1A 
    DDRD |= (1 << PD5);

    TCCR1A = (1 << WGM11) | (1 << WGM10) | (1 << COM1A0); // toggle OC1A på compare
    TCCR1B = (1 << WGM13) | (1<< WGM12)| (1 << CS10); // CTC, prescaler = 1, F-cpu = 4.9 Mhz
    OCR1A = 2; // 0,1,2,3 fungerer i område

   // 0.8192 mHz Mhz: 4.9 / 2*1 + (1+2)

    // min 0.5 mhz og maks 5mhz
    
    for (size_t i = 0; i < 4; i++)
    {
    adc_read_init();
    printf("jeg er her, adc_init \r\n");

   volatile uint8_t junk;
   junk = ADC_BASE[0];   // leser posisjon fra adc med 4 channels
   junk = ADC_BASE[0];
   junk = ADC_BASE[0];
   junk = ADC_BASE[0];

    }
    

}



/* Polling
void adc_read(uint8_t* jx, uint8_t* jy, uint8_t* tx, uint8_t* ty){
    ADC_BASE[0] = 0; //cs og write lav
        DDRD &= ~(1 << PD2); // PD2 som inngang for busy, sjekke når den blir aktiv høy
    while(!(PIND & (1 << PD2))){ //vente til busy ferdig. page 15 in adc datasheet
    ;
    printf("busy \r\n");
   };


    *jx = ADC_BASE[0]; // leser posisjon fra adc med 4 channels
    *jy = ADC_BASE[0];
    *tx = ADC_BASE[0];
    *ty = ADC_BASE[0];
}
*/

void adc_read_init(){
    ADC_BASE[0] = 0; //cs og write lav
}

void adc_read(volatile uint8_t* jx,volatile uint8_t* jy,volatile uint8_t* tx,volatile uint8_t* ty){
    /*DDRD &= ~(1 << PD2); // PD2 som inngang for busy, sjekke når den blir aktiv høy
    while(!(PIND & (1 << PD2))){ //vente til busy ferdig. page 15 in adc datasheet
        ;
        printf("busy \r\n");
     };
     */
    *jx = ADC_BASE[0]; // leser posisjon fra adc med 4 channels
    *jy = ADC_BASE[0];
    *tx = ADC_BASE[0];
    *ty = ADC_BASE[0];
}

void pos_calibrate(volatile uint8_t* jx,volatile uint8_t* jy,volatile uint8_t* tx,volatile uint8_t* ty, volatile pos_t *pos){
    
    // center values: tweak to your hardware
    //int16_t jx_raw = (int16_t)(*jx) - 70;
    //int16_t jy_raw = (int16_t)(*jy) - 70;
    //int16_t tx_raw = (int16_t)(*tx) - 128;
    //int16_t ty_raw = (int16_t)(*ty) - 128;

    // scale to roughly -100..100
    pos->joystick_x = (uint8_t)((*jx - 62) * 113 / 100);
    pos->joystick_y = (uint8_t)((*jy - 62) * 113 / 100);
    pos->touchpad_x = (uint8_t)( (*tx ) * 200 / 255 );
    pos->touchpad_y = (uint8_t)( (*ty ) * 200 / 255 );

}


void pos_print(volatile pos_t *pos,  volatile  dir*d){
    printf("joystick x: %d\r\n", pos->joystick_x);
    printf("joystick y: %d\r\n", pos->joystick_y);
    printf("touchpad x: %d\r\n", pos->touchpad_x);
    printf("touchpad y: %d\r\n", pos->touchpad_y);
    printf("direction joystick %s \r\n", dir_str(*d));

};


void pos_direction(volatile pos_t *pos, dir volatile *d) {
    int d_x = pos -> joystick_x;
    int d_y = pos -> joystick_y;
    if (abs(d_y-100) >= abs(d_x-100)){
        if (pos->joystick_y < 60){
        *d = DOWN;
    } else if (pos->joystick_y > 140){
        *d = UP;
    } else {
        *d = NEUTRAL;
    }
    
}else {
    if (pos->joystick_x < 60){
        *d = LEFT;
    } else if(pos->joystick_x > 140) {
        *d = RIGHT;
    } else{
        *d = NEUTRAL;
    }
}
}


const char *dir_str(dir d){
    switch (d)
        {
        case LEFT:
            return "left";
        case RIGHT:
            return "right";
        case UP:
            return "up";
        case DOWN:
            return "down";
        case NEUTRAL:
            return "neutral";
        default:
            return "unknown";
}
}

void position_update(uint8_t volatile *jx,uint8_t volatile *jy,uint8_t volatile  *tx,uint8_t  volatile *ty,pos_t volatile *pos, dir volatile *d){ 
    adc_read_init();
    if(control_flag){
      control_flag = 0; // clear flagg
    }

/*  Inni while */
    adc_read(jx, jy, tx, ty);
    pos_calibrate(jx, jy, tx, ty, pos);
    pos_direction(pos, d);
 //   pos_print(pos, d);
    printf("jeg er her, pos_update \r\n");
  
}
