#include "interrupt.h"


/*Interrupt */

void init_interrupt(){
    cli();

    /* setter INT2/PD2 som inngang*/
    DDRD &= ~(1 << PD2);

    /*Trigger på stigende flanke (busy går høy når konverteringen er ferdig)*/
   // MCUCR |= (1 << ISC01) | (1 << ISC00);

    MCUCR |= (1 << ISC2); // 
    
    /*Enable INT2*/
    GICR |= (1 << INT2);

    sei();
}




ISR(INT2_vect){
    control_flag = 1; // wake up
 //   adc_read(&jx, &jy, &tx, &ty);
    adc_read(&jx,&jy,&tx,&ty);
}