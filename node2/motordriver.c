#include "motordriver.h"

void pwm_motor_driver(){ // encoder eller motor
    PMC -> PMC_PCER0 |= (1 << ID_PIOB);
    PMC -> PMC_PCER1 = PMC_PCER1_PID36; //klokke for pwm
    PIOB -> PIO_PDR = PIO_PDR_P12; // disable PIO
    PIOB -> PIO_ABSR = PIO_ABSR_P12; // AB peripheral select
    
    // sette frekvens
    // sette duty cycle
    REG_PWM_CMR1 = PWM_CMR_CPRE_MCK_DIV_32 ; // PWM channel mode reg - left aligned - masterclock/32
    REG_PWM_CPRD1 = 52500; // PWM channel period reg
    REG_PWM_CDTY1 = 52500 - 2370; // PWM channel duty cycle reg

    PWM -> PWM_ENA = PWM_ENA_CHID0; // enable channel 0
    
    
    

}

void encoder_driver(){
    PMC -> PMC_PCER0 |= PMC_PCER0_PID13;
    PMC -> PMC_PCER0 |= PMC_PCER0_PID29; //klokke for TC2

  
    PIOC -> PIO_PDR = PIO_PDR_P26 | PIO_PDR_P25; // disable periperal
    PIOC -> PIO_ABSR |= PIO_ABSR_P26 | PIO_ABSR_P25; // B peripheral select
    PIOC->PIO_ODR  = PIO_ODR_P25 | PIO_ODR_P26;   // input    
    PIOC->PIO_PUER  = PIO_PUER_P25 | PIO_PUER_P26; 
    
    TC2 -> TC_BMR = TC_BMR_QDEN | TC_BMR_POSEN | TC_BMR_EDGPHA | TC_BMR_FILTER;

    TC2 ->TC_CHANNEL[0].TC_CMR = TC_CMR_TCCLKS_XC0;
    TC2 ->TC_CHANNEL[0].TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG;

    
}


void motor_driver(){

   
}

uint32_t read_encoder(){
    uint32_t cv   = TC2->TC_CHANNEL[0].TC_CV;   // posisjon
    uint32_t qisr = TC2->TC_QISR;               // QDEC status: DIR, IDX, QERR, MPE

    int dir = (qisr & TC_QISR_DIR) ? 1 : 0;     // 1 = opp, 0 = ned
    int idx = (qisr & TC_QISR_IDX) ? 1 : 0;
    int qer = (qisr & TC_QISR_QERR) ? 1 : 0;
    

    printf("QDEC: CV=%lu DIR=%d IDX=%d QERR=%d \r\n",
           (unsigned long)cv, dir, idx, qer);

    return cv;
}