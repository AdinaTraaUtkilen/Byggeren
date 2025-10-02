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
    for(size_t i = 0; i < 5; i++){
        leds_change_state(0, i);

    }

}
