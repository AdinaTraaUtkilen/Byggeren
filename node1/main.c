
#define F_CPU 4915200UL

#include "avr/io.h"
#include "util/delay.h"
#include "stdio.h"
#include "uart.h"
#include "sram.h"
#include "adc.h"
#include "spi.h"
#include "oled.h"
#include "interrupt.h"
#include "global.h"
#include "avr.h"
#include "labtester.h"
#include "mcp2515.h"
#include "can.h"

#define BAUD 9600
#define MYUBRR F_CPU / 16 / BAUD - 1


volatile uint8_t jx = 0, jy = 0, tx = 0, ty = 0, bp = 0;
volatile pos_t pos;
volatile dir d = NEUTRAL;
volatile uint8_t control_flag = 0;
volatile Buttons btn;
volatile homescreen_arrow arrow = PLAY_A;
volatile pages page = HOME;


int main()
{
  USART_Init(MYUBRR);
  xmem_init();
  adc_init();
  init_interrupt();
  spi_master_init();
  led_init(); 
  oled_init();
  oled_home();
  mcp2515_init();
  can_init();
  can_message m = {0x123, 5, {0}};

  can_message* message_ptr = &m;

  adc_read_init();
  if(control_flag){
      control_flag = 0; // clear flagg
    }


 while (1)
 {  
  menu_test(&jx, &jy,&tx, &ty, &pos, &d, &btn, &page, &arrow);
 
  
  message_ptr -> data[0]= pos.joystick_x;
  message_ptr -> data[1]= pos.joystick_y;
  message_ptr -> data[2]= pos.touchpad_x;
  message_ptr -> data[3]= pos.touchpad_y;
  message_ptr -> data[4]= pos.btn_pressed;
 
  //bit_modify_test();
 // printf("message numeber: %x \r\n", message_ptr->data[0]);
 // _delay_ms(200);
  can_message_send(message_ptr);
  //position_test(&jx, &jy,&tx, &ty, &pos, &d, control_flag);
  _delay_ms(500);
 
 }
  return 0;
};



 /*
  can_message rx;
  if (can_message_receive(&rx)) {
      printf("RX id=0x%03X len=%d data:", rx.id, rx.length);
      for (int k=0;k<rx.length;k++) {
          printf(" %02x", rx.data[k]);
         
          _delay_ms(2);
      }
       printf("\r\n");
      }
 };
 */