

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



/*
 * Remember to update the Makefile with the (relative) path to the uart.c file.
 * This starter code will not compile until the UART file has been included in the Makefile. 
 * If you get somewhat cryptic errors referencing functions such as _sbrk, 
 * _close_r, _write_r, _fstat etc, you have most likely not done that correctly.

 * If you get errors such as "arm-none-eabi-gcc: no such file", you may need to reinstall the arm gcc packages using
 * apt or your favorite package manager.
 */
//#include "../path_to/uart.h"

int main()
{
    SystemInit();

    CanInit init={0};
    uint8_t rxInterrupt=0;

    pwm_servo_driver();
    servo_driver();
    encoder_driver();

    WDT->WDT_MR = WDT_MR_WDDIS; // disable Watchdog Timer

    uart_init(F_CPU, BAUD); //bruk ACM1

    can_init( init, rxInterrupt);

    ir_init();
    CanMsg rx;
    

    
    while (1)
    {

        uint32_t encoder_value = read_encoder();
        printf("ENCODER VALUE : %x \r\n", encoder_value);


        uint8_t read_can = can_rx(&rx);

        if(read_can){
            //can_printmsg(rx);
            //printf("\r\n");
            joystick_to_pwm(&rx);
        }



        uint16_t ir_signal = ir_read();
        float ir_filtered = ir_filter_signal(ir_signal);
        float ir_filtered_volt =  ir_filtered * 3.3f / 4095.0f;


        //printf("IR signal: %.3f\r\n", ir_filtered_volt); // i volt fra 12 bit siden ADCen er det
        uint8_t score = update_game(ir_filtered_volt);

        //printf("score tid er naa: %d \r\n ", score);


    }
    
}        