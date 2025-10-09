#include "oled.h"

//128 x 64 dot matrix panel

//f D/C# pin is HIGH, D[7:0] is interpreted as display data written to Graphic Display Data RAM (GDDRAM).
//If it is LOW, the input at D[7:0] is interpreted as a command. Th


void oled_init(){

    oled_write_command(0xAE); // display off 

    oled_write_command(0x20); //page adressing
    oled_write_command(0x02);

    oled_write_command(0xA1);// segment remap - horizontal
    oled_write_command(0xC8); // scan direction

    oled_write_command(0xD3); // offset
    oled_write_command(0x00); 
    oled_write_command(0x40); // startline med offset lik 0

    oled_write_command(0xAF); // display on
 
}


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
    oled_pos(0, 123);
    oled_write_data (0b00011000) ;
    oled_write_data (0b00011000) ;
    oled_write_data (0b01111110) ;
    oled_write_data (0b00111100) ;
    oled_write_data (0b00011000) ;
}



void oled_goto_page(uint8_t page){
    oled_write_command(0xB0 | (page & 0x07));

}

void oled_goto_column(uint8_t column){
    oled_write_command(0x00 | (column & 0x0F));
    oled_write_command(0x10 | ((column >> 4) & 0x0F));
};

void oled_clear_all(){

    for (size_t i = 0; i < 8; i++)
    {
        oled_clear_page(i);
       
    }

}


void oled_clear_page(uint8_t page){
    oled_goto_page(page);
    oled_goto_column(0);

    for (size_t i = 0; i < 128; i++)
    {  
        oled_write_data(0x00);
    }
    
};


void oled_clear_column(uint8_t column){
     for (size_t i = 0; i < 128; i++)
    {
        oled_goto_page(i);
        oled_goto_column(column);
        oled_write_data(0x00);
    }

};

void oled_pos(uint8_t page, uint8_t column){
    oled_goto_page(page);
    oled_goto_column(column);
}


void oled_print(char c,uint8_t page,  uint8_t column){
    uint8_t i, idx = font_index(c);

    oled_pos(page, column);

    for(size_t i = 0; i < 8; i++){
        uint8_t col = pgm_read_byte(&font8[idx][i]);
        oled_write_data(col);
    }
}

/*

void oled_home();

void oled_set_brightness(lvl); // 256-step brightness control. 

*/


