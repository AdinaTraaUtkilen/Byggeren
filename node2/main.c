

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
#include "pwm.h"


void delay_ms(uint32_t ms){
    uint32_t count = (SystemCoreClock /10000)*ms;
    while (count--){
        __asm__("nop");
    }
}

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

    pwm_driver();
    servo_driver();

    WDT->WDT_MR = WDT_MR_WDDIS; // Enable Watchdog Timer

    uart_init(F_CPU, BAUD); //bruk ACM1

    can_init( init, rxInterrupt);
    

    CanMsg rx;
    
    while (1)
    {
        uint8_t read_can = can_rx(&rx);
        if(read_can){
            can_printmsg(rx);
            printf("\r\n");
            joystick_to_pwm(&rx);
        }
        

    }
    
}