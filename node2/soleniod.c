#include "soleniod.h"


void soleniod_init(){
    PMC -> PMC_PCER0 |= (1 << ID_PIOA);

    // pherihal, output og data
    PIOA -> PIO_PER = PIO_PA24;
    PIOA -> PIO_OER = PIO_PA24;
    PIOA -> PIO_SODR = PIO_PA24;


}


void run_soleniod(CanMsg* message){
    uint8_t btn_pressed = message->byte[4];
   
    if(btn_pressed){
      //  printf("");
        PIOA -> PIO_CODR = PIO_PA24;
        // aktiv lav litt, pulseee
    }else{
        PIOA -> PIO_SODR = PIO_PA24;
    } 
};