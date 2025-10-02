#include "oled.h"

//128 x 64 dot matrix panel

//f D/C# pin is HIGH, D[7:0] is interpreted as display data written to Graphic Display Data RAM (GDDRAM).
//If it is LOW, the input at D[7:0] is interpreted as a command. Th


void oled_init(){

    oled_write_command(0xAE); // display off 
    oled_write_command(0xA1);// segment remap - horizontal
     
    oled_write_command(0xC8); // scan direction
    oled_write_command(0xAF); // display on
 
}

void oled_reset(){

};



void oled_write_data(char data){
    spi_cd_data();
    spi_activate_disp_cs();
    spi_master_transmit(data);
    spi_deactivate_all();

};

void oled_write_command(char data){  
    spi_cd_command();
    spi_activate_disp_cs();
    spi_master_transmit(data);
    spi_deactivate_all();

}; 

void oled_print_arrow ( )
{

    oled_write_data (0b00011000) ;
    oled_write_data (0b00011000) ;
    oled_write_data (0b01111110) ;
    oled_write_data (0b00111100) ;
    oled_write_data (0b00011000) ;
}

void oled_home();

void oled_goto_page(line);

void oled_goto_column(column){

};

void oled_clear_page(line){
    for (size_t i = 0; i < 128; i++)
    {
        oled_write_data


















        
    }
    
};

void oled_clear_all(){
    for(size_t page = 0; page < 8; page++){
        segment=00000000
    }
    

}

void oled_clear_column(colum){

};

void oled_pos(row, column);


void oled_print(char*);

void oled_set_brightness(lvl); // 256-step brightness control. 


