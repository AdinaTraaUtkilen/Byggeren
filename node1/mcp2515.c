#include "mcp2515.h"

// cs = PB0 mcp
// interrupt 12 = pe0 / int2



void mcp2515_init(){
   spi_deactivate_all();
   mcp2515_reset();

}



uint8_t mcp2515_read(uint8_t address){
    spi_activate_can_cs();
    spi_master_transmit(0x03); // read command
    spi_master_transmit(address); // send adreess

    uint8_t data = spi_master_transfer(0x00);
    spi_deactivate_all();

    return data;
}



void mcp2515_reset(){
    spi_activate_can_cs();
    spi_master_transmit(0b11000000); // reset command
    spi_deactivate_all();
}



void mcp2515_write(uint8_t address, uint8_t data){
    spi_activate_can_cs();
    spi_master_transmit(0x02); // write command
    spi_master_transmit(address); // adress
    spi_master_transmit(data);// data

    spi_deactivate_all();
}


uint8_t read_status(){
    spi_activate_can_cs();
    spi_master_transmit(0b10100000); // read status command

    uint8_t status = spi_master_transfer(0x00);

    spi_deactivate_all();
    return status;
}



void mcp2515_bit_modify(uint8_t address, uint8_t mask, uint8_t new_data){
    spi_activate_can_cs();
    spi_master_transmit(0x05); // bit modify command
    spi_master_transmit(address); // address
    spi_master_transmit(mask); // mask
    spi_master_transmit(new_data); // data

    spi_deactivate_all();
}



void mcp2515_request_to_send(uint8_t buffer){
    spi_activate_can_cs();
    spi_master_transmit(0b10000000 | buffer); // request to send command

    spi_deactivate_all();
}