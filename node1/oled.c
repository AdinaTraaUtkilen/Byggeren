

#include "oled.h"
#include "fonts.h"
#include <string.h>




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


void oled_home(){
    oled_clear_all();
    oled_print_str("MENU", 0, 50, 8);
    oled_print_str("PLAY ", 2, 0, 4);
    oled_print_str("SCOREBOARD", 4, 0, 4);

    oled_print_arrow(2, 40);

}


void oled_change_arrow(volatile dir* d,  volatile homescreen_arrow* arrow){

    switch (*d)
    {
    case DOWN:
        if (*arrow == PLAY_A){
            oled_clear_page(2);
            oled_print_str("PLAY ", 2, 0, 4);
            oled_print_arrow(4, 88);
            *arrow=SCOREBOARD_A;
        }
   
        break;

        case UP:
        if (*arrow == SCOREBOARD_A){
            oled_clear_page(4);
            oled_print_str("SCOREBOARD", 4, 0, 4);
            oled_print_arrow(2, 40);
            *arrow=PLAY_A;   
        }
        break;
    
    default:
        break;
    }
        
}

void led_play(){
    led_on(2);
    led_on(3);
    _delay_ms(40);
    led_off(2);
    led_off(3);
    _delay_ms(40);
    led_on(1);
    led_on(4);
    _delay_ms(40);
    led_off(1);
    led_off(4);
    _delay_ms(40);
    led_on(0);
    led_on(5);
    _delay_ms(40);
    led_off(0);
    led_off(5);
      
}

void led_scoreboard(){
    for (size_t i=0; i<7; i++){
        led_on(i);
        _delay_ms(2);
    }
    
    _delay_ms(40);
    
    for (size_t i=6; i>=0; i--){
        led_off(i);
        _delay_ms(2);
    }
    _delay_ms(40);

}

void change_page(volatile pages *page,volatile  homescreen_arrow *arrow, volatile Buttons *btn){
    switch(*arrow)
    {
    case PLAY_A:
        oled_clear_all();
        oled_print_str("Lets go!", 3, 30, 8);
        
        //led_play();
        
    
        *page = PLAY;
        break;
    case SCOREBOARD_A:
        oled_clear_all();
        oled_print_str("SCOREBOARD", 0, 20, 8);
        oled_print_str("1.", 2, 0, 4);
        oled_print_str("2.", 4, 0, 4);
        oled_print_str("3.", 6, 0, 4);
      //  led_play();
   
        *page = SCOREBOARD;
        break;
    default:
        break;
    }
}

void home_button(volatile Buttons *btn, volatile pages *page, volatile homescreen_arrow* arrow){
    if(btn->L7){
        oled_home();
        *page = HOME;
        *arrow = PLAY_A;

    }
}

void oled_update_score(uint8_t score){

    uint8_t last_displayed_score = 255; // Initialize to impossible value

    if (score != last_displayed_score) {
// Clear the score area (page 0, columns 90-128)
    oled_goto_page(0);
    oled_goto_column(90);
    for (uint8_t i = 0; i < 38; i++) {
    oled_write_data(0x00);
    }
    // Print "Score: XX"
    oled_print_str("Score:", 0, 90, 4);
    // Convert score to string and display
    char score_str[4];
    if (score < 10) {
    score_str[0] = '0' + score;
    score_str[1] = '\0';
    } else {
    score_str[0] = '0' + (score / 10);
    score_str[1] = '0' + (score % 10);
    score_str[2] = '\0';
    }
    oled_print_str(score_str, 0, 116, 4);
    last_displayed_score = score;
}
}