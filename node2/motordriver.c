#include "motordriver.h"

void pwm_motor_driver(){ // motor
    PMC -> PMC_PCER0 |= (1 << ID_PIOB);
    PMC -> PMC_PCER1 |= PMC_PCER1_PID36;// enable peripheral clock signal - 36
    PIOB -> PIO_PDR = PIO_PDR_P12; // disable PIO
    PIOB -> PIO_ABSR |= PIO_ABSR_P12; // AB peripheral select

    
    // sette frekvens
    // sette duty cycle
    REG_PWM_CMR0 = PWM_CMR_CPRE_MCK_DIV_32 ; // PWM channel mode reg - left aligned - masterclock/32
    REG_PWM_CPRD0 = 131; // PWM channel period reg
    
    PWM -> PWM_ENA = PWM_ENA_CHID0; // enable channel 0

    //phase dir pin
    PMC -> PMC_PCER0  |= (1u << ID_PIOC);
    PIOC -> PIO_PER = PIO_PC23;
    PIOC -> PIO_OER = PIO_PC23;  

    PIOC->PIO_SODR = PIO_PC23;

  

}

void encoder_driver_init(){
    PMC -> PMC_WPMR = 0x504D4300;
    if (PMC->PMC_WPMR & PMC_WPMR_WPEN){
        printf("Operation not permittted");
    }

    PMC-> PMC_PCER1 |= (1 << (ID_TC6 - 32)) | (1 << (ID_TC7 - 32)) ;


    PMC -> PMC_PCER0 |= PMC_PCER0_PID29; //klokke for TC28

    //sørger for at PA29 ikke driver linja
    PIOA -> PIO_PER |= PIO_PER_P29; //PIO-kontroll
    PIOA -> PIO_ODR |= PIO_ODR_P29; // input
    PIOA -> PIO_PUDR |= PIO_PUDR_P29; //ingen pull

    PIOC -> PIO_PDR |= PIO_PDR_P26 | PIO_PDR_P25; // disable periperal
    PIOC -> PIO_ABSR |= PIO_ABSR_P26 | PIO_ABSR_P25; // B peripheral select

    REG_TC2_WPMR |= (0x54494D << 8);
    REG_TC2_WPMR &= ~(TC_WPMR_WPEN); 

    REG_TC2_BMR = TC_BMR_QDEN | TC_BMR_POSEN | TC_BMR_EDGPHA ;

    
    int32_t last_encoder_value = 10;
    int32_t encoder_value = read_encoder();

    while (last_encoder_value != encoder_value)
    {
        PIOC -> PIO_CODR = PIO_PC23; // set dir forward
        REG_PWM_CDTYUPD0 = REG_PWM_CPRD0 - 50; // PWM channel duty cycle reg
        last_encoder_value = encoder_value;
        for (volatile uint32_t i=0; i<200000; ++i) __asm__("nop");
        encoder_value = read_encoder();
    }
    
    REG_PWM_CDTYUPD0 = REG_PWM_CPRD0 - 10; // PWM channel duty cycle reg

    TC2 -> TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_XC0;
    TC2 -> TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;

}


int32_t read_encoder(){
    volatile int32_t cv  = (int32_t)TC2->TC_CHANNEL[0].TC_CV * (-1);   // posisjon
    return cv;
}

void joystick_to_pwm_motor(CanMsg* message){
    
    uint8_t joystick_x= message->byte[0];
    if (joystick_x < 100){
        PIOC -> PIO_CODR = PIO_PC23; // set dir backwards
        uint32_t speed = REG_PWM_CPRD0 - joystick_x;
        REG_PWM_CDTYUPD0 = REG_PWM_CPRD0 - speed;

    }
    else if(joystick_x > 110){
        
        PIOC -> PIO_SODR = PIO_PC23; // set dir forward
        uint32_t speed = (joystick_x - 80);
        REG_PWM_CDTYUPD0 = REG_PWM_CPRD0 - speed;
    } else {
        REG_PWM_CDTYUPD0 = REG_PWM_CPRD0 - 10;
    }

    
}

uint32_t encoder_pos_func(int32_t encoder_value){
    int32_t encoder_pos;
    if (encoder_value < 0){
        encoder_pos = 0;

    } else{
        encoder_pos =  (uint32_t)floorf((float)(encoder_value / 28)); // 5610 / 200 span speed (var 28)
    }
    printf("encoder: %d \r\n", encoder_pos);
    return encoder_pos ;

}




void pi_motor_set_cdty(float u)
{
    if (u > 0) {
        // Forward
        PIOC->PIO_SODR = PIO_PC23; // set dir forward
    } else {
        // Backward
        PIOC->PIO_CODR = PIO_PC23; // set dir backward
        u = -u;
    }
   // printf("u : %f \r\n", u);

    uint32_t duty =(uint32_t)(u);
   // printf("dutyyyy %d \r\n", duty);
   
 
    REG_PWM_CDTYUPD0 = REG_PWM_CPRD0 - duty;
}
