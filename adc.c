#include <stdlib.h>
#include "adc.h"

volatile uint8_t *ADC_BASE = (uint8_t*)0x1400; //baseadresse ADC

void adc_init(void){
    // klokke output OC1A 
    DDRD |= (1 << PD5);

    TCCR1A = (1 << WGM11) | (1 << WGM10) | (1 << COM1A0); // toggle OC1A på compare
    TCCR1B = (1 << WGM13) | (1<< WGM12)| (1 << CS10); // CTC, prescaler = 1, F-cpu = 4.9 Mhz
    OCR1A = 2; // 0,1,2,3 fungerer i område

   // 0.8192 mHz Mhz: 4.9 / 2*1 + (1+2)

    // min 0.5 mhz og maks 5mhz
  
}


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

void pos_calibrate(uint8_t *jx, uint8_t* jy, uint8_t* tx, uint8_t* ty, pos_t *pos){
    
    pos->joystick_x =  (*jx - 160) * (100/90) ;
    pos->joystick_y = (*jy - 160) * (100/90);
    pos->touchpad_x = (*tx - 127.5) * (100/127.5);
    pos->touchpad_y = (*ty - 127.5) * (100/127.5);

}


void pos_read(pos_t pos, dir*  d){
    printf("joystick x: %d\r\n", pos.joystick_x);
    printf("joystick y: %d\r\n", pos.joystick_y);
    printf("touchpad x: %d\r\n", pos.touchpad_x);
    printf("touchpad y: %d\r\n", pos.touchpad_y);
    printf("direction joystick %s \r\n", dir_str(*d));

};


void pos_direction(pos_t *pos, dir *d) {
    int d_x = pos -> joystick_x;
    int d_y = pos -> joystick_y;
    if (abs(d_y) >= abs(d_x))
    {
        if (pos->joystick_y == 0){
        *d = NEUTRAL;
    } else if (pos->joystick_y < 0){
        *d = DOWN;
    } else if (pos->joystick_y > 0){
        *d = UP;
    }
}else {
    if (pos->joystick_x < 0){
        *d = LEFT;
    } else if(pos->joystick_x > 0) {
        *d = RIGHT;
    } else if (pos->joystick_x == 0){
        *d = NEUTRAL;
    }
}
}


char *dir_str(dir d){
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

