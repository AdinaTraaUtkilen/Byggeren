#include "pwm.h"
#include "sam.h"

void init_timer_pwm(){
    PMC -> PMC_PCER1 |= (1 << 4); // enable peripheral clock signal - 36
    PIO -> PIO_PDR |= PIO_PDR_P1; // disable PIO
    PIO -> PIO_ABSR |= PIO_ABSR_P1; // AB peripheral select
}