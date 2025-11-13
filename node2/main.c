

//#define F_CPU 4915200UL
#define BAUD 9600

#define F_CPU 84000000
//#define MYUBRR F_CPU / 16 / BAUD - 1

#include <stdio.h>
#include <stdarg.h>
#include "sam/sam3x/include/sam3x8e.h"
#include "sam/sam3x/include/sam.h"
#include "startcode/uart.h"
#include "startcode/can.h"
#include "startcode/time.h"
#include "servo.h"
#include "ir.h"
#include "motordriver.h"
#include "pi.h"
#include "soleniod.h"



volatile uint32_t pid_flag = 0;



int main()
{
    SystemInit();

    CanInit init={0};
    uint8_t rxInterrupt=0;

    WDT->WDT_MR = WDT_MR_WDDIS; // disable Watchdog Timer

    uart_init(F_CPU, BAUD); //bruk ACM1

    can_init( init, rxInterrupt);

    pwm_driver();
    servo_driver();
    pwm_motor_driver();
    encoder_driver_init();
   
    ir_init();
    CanMsg rx;

    pid_timer_init();
    soleniod_init();


    while (1)
    {

        int32_t encoder_value = read_encoder();
        uint32_t encoder_pos = encoder_pos_func(encoder_value);
    //    printf("encoder %d vs joystick %d \r\n", encoder_pos, rx.byte[0]);
        
        uint8_t read_can = can_rx(&rx);

        if(read_can){
            //can_printmsg(rx);
          //  printf("\r\n");
            joystick_to_pwm_servo(&rx);
         //   joystick_to_pwm_motor(&rx);
        }

        

        uint16_t ir_signal = ir_read();
        float ir_filtered_volt = ir_filter_signal(ir_signal);

     //   printf("IR signal: %.3f\r\n", ir_filtered_volt); // i volt fra 12 bit siden ADCen er det
        uint8_t score = update_game(ir_filtered_volt);


        if(pid_flag){
            pid_flag = 0; // clear flagg
            int32_t enc = encoder_pos;
            CanMsg current_ref = rx;
            position_controller(enc, &current_ref);
        }

       run_soleniod(&rx);

    }
    
}        