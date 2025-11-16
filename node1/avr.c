#include "avr.h"


void leds_change_state(uint8_t command, uint8_t led_num){
    spi_activate_io_cs();
    spi_master_transmit(0x05); // controll command
    
    spi_master_transmit(led_num);   // choose led 0 to 5
 
    spi_master_transmit(command); // on or off // 1
    spi_deactivate_all(); // SPI goes high again
    _delay_ms(40);
}




void led_on(uint8_t led_num){
    leds_change_state(1, led_num);
}



void led_off(uint8_t led_num){
    leds_change_state(0, led_num);
}



void led_init(){
    for(size_t i = 0; i < 6; i++){
        leds_change_state(0, i);
    }
}



void read_joystick_button( volatile pos_t *pos){
    spi_activate_io_cs();
    spi_master_transmit(0x03);
    _delay_us(40);
    uint8_t xpos = spi_master_receive(0x00);
    _delay_us(2);
    uint8_t ypos = spi_master_receive(0x00);
    _delay_us(2);
    uint8_t BTN_joy = spi_master_receive(0x00);
    spi_deactivate_all();
    pos->btn_pressed = BTN_joy;    
}




void update_buttons(volatile Buttons *btn){ 
    spi_activate_io_cs();
    spi_master_transmit(0x04);
    _delay_us(40);
    uint8_t right = spi_master_receive(0x00);
    _delay_us(2);
    uint8_t left = spi_master_receive(0x00);
    _delay_us(2);
    uint8_t nav = spi_master_receive(0x00);
    spi_deactivate_all();

    btn->right = right;
    btn->left = left;
    btn->nav = nav;
}