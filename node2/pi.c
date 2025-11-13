#include "pi.h"


extern volatile uint32_t pid_flag;
#define PI_DT 0.01f    // sampling time in seconds



float k_p = 0.8f;
float k_i = 0.4f;
float integral = 0;


void pid_timer_init(){
    PMC -> PMC_PCER0 |= (1 << ID_TC0); // enbale tc0

    TcChannel *ch = &TC0->TC_CHANNEL[0]; // use TC0 channel 0

    //Clock: TIMER_CLOCK4 = MCK/128 = 84 MHz / 128 = 656250 Hz
    //We want 100 Hz → RC = 656250 / 100 ≈ 6563
    ch->TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK4   // clock source
               | TC_CMR_WAVE                  // waveform mode
               | TC_CMR_WAVSEL_UP_RC;         // count up to RC, then reset

    ch->TC_RC = 6563;                         // 10 ms period

    ch->TC_IER = TC_IER_CPCS;           // Enable interrupt on RC compare

    REG_TC0_IER0 = (1 << TC_IER_COVFS); // compare

    
    NVIC_ClearPendingIRQ(TC0_IRQn); //clear flag

    NVIC_EnableIRQ(TC0_IRQn); //enable
    
    ch->TC_CCR = TC_CCR_CLKEN | TC_CCR_SWTRG; // start counter

} 



void TC0_Handler(){
    // Read status register to clear the interrupt flag
    uint32_t status = TC0->TC_CHANNEL[0].TC_SR;
    (void)status;

    pid_flag = 1;

}





void position_controller(uint32_t encoder_pos, CanMsg* message){
    int32_t error = message->byte[0] - encoder_pos;

 //   printf("error : %d \r\n", error);

    float p_part=k_p*error;

    float max_output  = 131.0f;
    float min_output = -131.0f;

    float i_part = k_i * integral;
    float u_temp = p_part + i_part;

    if ((u_temp < max_output && u_temp > min_output)||(u_temp >= max_output && error < 0)||(u_temp <= min_output && error > 0)) {
        integral = integral + error;
    }

    int32_t max_integral = 20;
    int32_t min_integral = -20;

    if (integral >= max_integral)
    {
        integral = max_integral;
    } else if (integral <= min_integral)
    {
        integral = min_integral;
    }

    i_part = k_i*integral;
    
    
   // printf("print p part %f \r\n", p_part);
   // printf("print i part %f \r\n", i_part);

    float u = p_part + i_part;
    
   
    pi_motor_set_cdty(u);

}
