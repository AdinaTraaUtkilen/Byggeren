#include "pwm.h"


#define F_CPU 84000000


void pwm_driver(){
    PMC -> PMC_PCER0 |= (1 << ID_PIOB);
    PMC -> PMC_PCER1 = PMC_PCER1_PID36;// enable peripheral clock signal - 36
    PIOA -> PIO_PDR = PIO_PDR_P13; // disable PIO
    PIOA -> PIO_ABSR = PIO_ABSR_P13; // AB peripheral select

}


  void servo_driver(){
   
    REG_PWM_CMR1 = PWM_CMR_CPRE_MCK_DIV_32 ; // PWM channel mode reg - left aligned - masterclock/32
    REG_PWM_CPRD1 = 52500; // PWM channel period reg
    REG_PWM_CDTY1 = 3938; // PWM channel duty cycle reg
    REG_PWM_CDTYUPD1 =3938; // update
    PWM -> PWM_ENA = PWM_ENA_CHID1; // enable register


  }