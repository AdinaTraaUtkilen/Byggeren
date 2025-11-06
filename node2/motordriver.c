#include "motordriver.h"

void pwm_motor_driver(){ // encoder eller motor
    PMC -> PMC_PCER0 |= (1 << ID_PIOB);
    PMC -> PMC_PCER1 = PMC_PCER1_PID36; //klokke for pwm
    PIOB -> PIO_PDR = PIO_PDR_P12; // disable PIO
    PIOB -> PIO_ABSR |= PIO_ABSR_P12; // AB peripheral select
    
    // sette frekvens
    // sette duty cycle
    REG_PWM_CMR1 = PWM_CMR_CPRE_MCK_DIV_32 ; // PWM channel mode reg - left aligned - masterclock/32
    REG_PWM_CPRD1 = 52500; // PWM channel period reg
    REG_PWM_CDTY1 = 52500 - 2370; // PWM channel duty cycle reg

    PWM -> PWM_ENA = PWM_ENA_CHID0; // enable channel 0
    
    
    

}

void encoder_driver_init(){
    PMC -> PMC_WPMR = 0x504D4300;
    PMC -> PMC_PCER0 |= (1 << ID_PIOA);
    PMC -> PMC_PCER0 |= (1 << ID_PIOC);
   // PMC -> PMC_PCER0 |= PMC_PCER0_PID13; // output C
    // PMC -> PMC_PCER0 |= PMC_PCER0_PID11; // output A

    PMC -> PMC_PCER0 |= PMC_PCER0_PID29; //klokke for TC2

    //sørger for at PA29 ikke driver linja
    PIOA -> PIO_PER |= PIO_PER_P29; //PIO-kontroll
    PIOA -> PIO_ODR |= PIO_PER_P29; // input
    PIOA -> PIO_PUDR |= PIO_PER_P29; //ingen pull

    PIOC -> PIO_PDR |= PIO_PDR_P26 | PIO_PDR_P25; // disable periperal
    PIOC -> PIO_ABSR |= PIO_ABSR_P26 | PIO_ABSR_P25; // B peripheral select
    PIOC -> PIO_OER  |= PIO_OER_P25 | PIO_OER_P26;   // input
//    PIOC -> PIO_IFER = PIO_IFER_P25 | PIO_IFER_P26;
  //  PIOC->PIO_PUDR  = PIO_PUDR_P25 | PIO_PUDR_P26; 
    REG_TC2_WPMR = (0x54494D << 8);
 //   TC2 -> TC_BMR = TC_BMR_QDEN | TC_BMR_POSEN | TC_BMR_EDGPHA ;
    TC2 -> TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_XC0;
    TC2 -> TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;
    REG_TC2_BMR = TC_BMR_QDEN | TC_BMR_POSEN | TC_BMR_EDGPHA ;
  
    
}



uint32_t read_encoder(){
   // PIOC -> PIO_OER = PIO_OER_P26 | PIO_OER_P25; 

    volatile uint32_t cv  = TC2->TC_CHANNEL[0].TC_CV;   // posisjon
   // printf("QDEC: CV=%lu ", cv);
    uint32_t bmr = REG_TC2_BMR;

    

    printf("bmr: %x \r\n", bmr);

    uint32_t wpm = TC2 -> TC_WPMR;
    printf("wpmr: %x \r\n", wpm);
    
  //  PIOC -> PIO_ODR = PIO_ODR_P26 | PIO_ODR_P25; 

    return cv;
}