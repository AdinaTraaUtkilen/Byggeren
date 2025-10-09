#include "oled.h"
#include "fonts.h"
#include <string.h>
#include "global.h"


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

    oled_clear_all();
 
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

void oled_print_arrow (uint8_t page, uint8_t column )
{
    oled_pos(page, column);
    oled_write_data (0b00011000) ;
    oled_write_data (0b00111100) ;
    oled_write_data (0b01111110) ;
    oled_write_data (0b00011000) ;
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
}

void oled_pos(uint8_t page, uint8_t column){
    oled_goto_page(page);
    oled_goto_column(column);
}


void oled_print_char(char c,uint8_t page, uint8_t column, uint8_t font){
    uint8_t index = font_index(c);

    oled_pos(page, column);


    switch (font)
    {
    case 8:
        for(size_t i = 0; i < 8; i++){
        uint8_t col = pgm_read_byte(&font8[index][i]);
        oled_write_data(col);
    }
        break;
    case 5:   oled_write_data (0b00111100) ;
    oled_write_data (0b00011000) ;
        for(size_t i = 0; i < 5; i++){
        uint8_t col = pgm_read_byte(&font5[index][i]);
        oled_write_data(col);
    }
        break;
    case 4:
        for(size_t i = 0; i < 4; i++){
        uint8_t col = pgm_read_byte(&font4[index][i]);
        oled_write_data(col);
    }
        break;
    default:
        break;
    }
   
}
    


void oled_print_str(const char *str,uint8_t page, uint8_t column,uint8_t font){
    uint8_t i = 0;
    uint8_t current_col = column;
    uint8_t current_page = page;

    while (str[i] != '\0'){
        if (current_col + 8 > 128){
            current_col = 0;
            current_page++;
            if (current_page == 8){
                current_page = 0;
            }
            oled_print_char(str[i], current_page, current_col, font);
    } else{
        oled_print_char(str[i], current_page, current_col, font);
        
    }
    i++;
    current_col += 8;
}
}

uint8_t font_index(char c) {
    if (c < 32 || c > 126) return 0; 
    return (uint8_t)(c - 32);
}






void oled_home(volatile dir* d,  volatile homescreen_menu* current_position){
    oled_print_str("MENU", 0, 50, 8);
    oled_print_str("PLAY ", 2, 0, 4);
    oled_print_str("SCOREBOARD", 4, 0, 4);
    
    switch (*d)
    {
    case DOWN:
        if (*current_position == PLAY){
            oled_clear_page(2);
            oled_print_str("PLAY ", 2, 0, 4);
            oled_print_arrow(4, 88);
            *current_position=SCOREBOARD;

        }
        else if (*current_position == SCOREBOARD){
            oled_clear_page(4);
            oled_print_str("SCOREBOARD", 4, 0, 4);
            oled_print_arrow(2, 40);
            *current_position=PLAY;

        }
        break;

        case UP:
        if (*current_position == PLAY){
            oled_clear_page(2);
            oled_print_str("PLAY ", 2, 0, 4);
            oled_print_arrow(4, 88);
            *current_position=SCOREBOARD;

        }
        else if (*current_position == SCOREBOARD){
            oled_clear_page(4);
            oled_print_str("SCOREBOARD", 4, 0, 4);
            oled_print_arrow(2, 40);
            *current_position=PLAY;

        }
        break;
    
    default:
        break;
    }
        
}