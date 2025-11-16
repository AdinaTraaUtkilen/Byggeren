#include <stdlib.h>
#include "labtester.h"



  //   ---------------------- oving 1 -----------------------------------
void test_uart(){
  volatile uint32_t *ext_mem = (volatile uint32_t*) external_mem_baseadress;
  ext_mem[1200] = 0x55; // 0101 0101,
  _delay_ms(1500);

  PORTD ^= (1 << PD2);

  unsigned char c = USART_Receive();
  USART_Transmit(c);

  printf("Test");

}



  //   ---------------------- oving 2 - oppg.1 -----------------------------------
void manual_latch_test(){ // styrer pinene direkte utifra høy/lav latch
   // setter som output

  DDRD |= (1 << PD2);
  DDRE |= (1 << PE1); // PE til LE, latch enable PE1 = ALE!!!
  DDRA |= 0xFF;         // pa0 til pa7 til latch

  PORTE &= ~(1 << PE1); // holde le lav, holder Q

  PORTA = 0b01010101;
  PORTE |= (1 << PE1);  // LE høy, sende gjennom
  PORTE &= ~(1 << PE1); // Le lav, låse verdien

  PORTA = 0b10101010; // D endres, Q uendret
}




// --------------------------  oving 2 - oppg. 2 & 4---------------------------------------
void sram_test_func(){ // ekstern minne tar over 

  SRAM_test();
  volatile uint8_t *ADC_REG = (uint8_t*)0x1400; // peker til adc, hvor a11 er 0
  volatile uint8_t *SRAM_REG = (uint8_t*)0x1800; // peker til stram, hvor a11 er 1, og blir invertert i nand
}




// --------------------------  oving 3---------------------------------------
void position_test(uint8_t *jx,uint8_t *jy,uint8_t *tx,uint8_t *ty,pos_t *pos, dir *d, volatile uint8_t *control_flag){ 

  /*Inni while*/
   adc_read(jx, jy, tx, ty);
  pos_calibrate(jx, jy, tx, ty, pos);
   pos_direction(pos, d);
  pos_print(pos, d);
}




// --------------------------  oving 4---------------------------------------
void spi_test(){
  spi_activate_disp_cs();
  spi_master_transmit(0xAA); //dummy
  _delay_ms(200);

  volatile uint8_t trash; // nullstille flagget
  trash = SPSR;
  trash = SPDR;
}


void led_test(){
   led_on(0);
  _delay_us(40);
  led_on(1);
  _delay_us(40);
  led_on(2);
  _delay_us(40);
  led_on(3);
  _delay_us(40);
  led_on(4);
  _delay_us(40);
  led_on(5);
  _delay_us(40);


    led_off(0);
  _delay_us(40);
  led_off(1);
  _delay_us(40);
  led_off(2);
  _delay_us(40);
  led_off(3);
  _delay_us(40);
  led_off(4);
  _delay_us(40);
  led_off(5);
  _delay_us(40);
    

}


void menu_test(uint8_t *jx,uint8_t *jy,uint8_t *tx,uint8_t *ty, volatile pos_t *pos, volatile dir *d, volatile Buttons *btn, volatile pages *page, volatile homescreen_arrow *arrow){
 position_update(jx,jy,tx,ty,pos, d);
 pos_print(pos, d);
  read_joystick_button(pos);
  update_buttons(btn);
  
  if(*page == HOME){
      oled_change_arrow(d, arrow);
  }

  if (pos->btn_pressed == 1){
    change_page(page, arrow, btn);
  }
  home_button(btn, page,arrow);
 
 // _delay_ms(50);
  
}


// --------------------------  oving 4---------------------------------------
void bit_modify_test(){
  uint8_t address = 0b00001111;
  uint8_t data = 0b00000000;
  uint8_t mask = 0b11110000;

  mcp2515_write(address, data);
  uint8_t data_recevied = mcp2515_read(address);
  
  printf("data sendt og fatt tilbake: %d \r\n", data_recevied);

  uint8_t new_data = 0b11111111;

  mcp2515_bit_modify(address, mask, new_data);
  uint8_t data_recevied_mod = mcp2515_read(address);

  //240
  printf("data sendt og fatt og modifiserrt tilbake: %d \r\n", data_recevied_mod);
 
}

// --------------------------  oving 4---------------------------------------
void send_joystick_pos(can_message *message_ptr){
  message_ptr -> data[0]= (uint8_t)pos.joystick_x;
  message_ptr -> data[1]= (uint8_t)pos.joystick_y;
  message_ptr -> data[2]= (uint8_t)pos.touchpad_x;
  message_ptr -> data[3]= (uint8_t)pos.touchpad_y;
  message_ptr -> data[4]= (uint8_t)pos.btn_pressed;

  can_message_send(message_ptr);

  can_message rx;
  if (can_message_receive(&rx)) {
      printf("RX id=0x%03X len=%d data:", rx.id, rx.length);
      for (int k=0;k<rx.length;k++) {
          printf(" %02d", rx.data[k]);
         
          _delay_ms(2);
      }
       printf("\r\n");
      }
 };