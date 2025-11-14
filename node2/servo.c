#include "servo.h"


#define F_CPU 84000000


void pwm_driver(){
    PMC -> PMC_PCER0 |= (1 << ID_PIOB);
    PMC -> PMC_PCER1 |= PMC_PCER1_PID36;// enable peripheral clock signal - 36
    PIOB -> PIO_PDR |= PIO_PDR_P13; // disable PIO
    PIOB -> PIO_ABSR |= PIO_ABSR_P13; // AB peripheral select

}


  void servo_driver(){
    REG_PWM_CMR1 = PWM_CMR_CPRE_MCK_DIV_32 ; // PWM channel mode reg - left aligned - masterclock/32
    REG_PWM_CPRD1 = 52500; // PWM channel period reg
    REG_PWM_CDTY1 = 52500 - 2370; // PWM channel duty cycle reg
    PWM -> PWM_ENA |= PWM_ENA_CHID1; // enable register

  }


  void check_min_max(uint16_t reg_duty_cycle){

    uint16_t D_min=52500 - 2625; // 52500-2370
    uint16_t D_max= 52500 - 5250; // 52500-5500

    if (reg_duty_cycle>D_min){
        REG_PWM_CDTY1=D_min;
    }
    else if (reg_duty_cycle<D_max){
        REG_PWM_CDTY1=D_max;
    }
    else{
        REG_PWM_CDTY1 = reg_duty_cycle;
   
    }
        
}


void joystick_to_pwm_servo(CanMsg* message){
    uint8_t joystick_y= message->byte[1];  
    uint16_t D_tic = 52500 - (13*joystick_y) - 2625;
    check_min_max(D_tic);
    
}

