
#define F_CPU 4915200UL
#include "can.h"
#include "util/delay.h"


void can_init(){
    mcp2515_reset();
    _delay_ms(50);
    uint8_t config_mode = 0b10000000;
    uint8_t loopback_mode = 0b01000000;

    uint8_t rx_interrupt = 0x03;
    uint8_t loopback_flag = 0x03;

    mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, loopback_mode); // CanControll register
    mcp2515_bit_modify(MCP_CANSTAT, MODE_MASK, loopback_mode); // CanStatus register

    /*
     mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, config_mode); // CanControll register
    mcp2515_bit_modify(MCP_CANSTAT, MODE_MASK, config_mode); // CanStatus register
      uint8_t inter = mcp2515_read(MCP_CANINTE);
     printf(" interrupt before config(CANINTE=0x%02X)\r\n", inter ) ;


 //   mcp2515_bit_modify(MCP_CANINTE, loopback_interrupt, );
  // 
    uint8_t canstat2 = mcp2515_read(MCP_CANCTRL);
    if (( config_mode & MODE_MASK ) != MODE_CONFIG ) {
        printf(" MCP2515 is NOT in configuration mode after reset (CANSTAT=0x%02X)\r\n", canstat2 ) ;
    }
   
     mcp2515_bit_modify(MCP_CANINTF, 0xFF, 0x00); //rydder flagg, alle mask lik 1 og flag = 0
     mcp2515_write(MCP_CANINTE, rx_interrupt); // enable rx interrupts
     */

}



void can_message_send(can_message *message){
    uint8_t pending_buffer = mcp2515_read(MCP_TXB0CTRL);
    while(pending_buffer & (1 << 3)){
    };
    uint8_t sid31 = ((message->id) >> 3) & 0xFF;
    uint8_t sid32 = ((message->id) & 0x07) << 5;

    mcp2515_write(0x31, sid31);
    mcp2515_write(0x32, sid32); // id
    
    mcp2515_write(0x35, (message->length & 0x0F)); //length

    for (uint8_t i = 0; i < message->length; i++){ // skrive data
        mcp2515_write(0x36 + i, message->data[i]);
    }

    mcp2515_request_to_send(0x01); // buffer 0

}

bool can_message_receive(can_message *m_out){ 
    uint8_t intf = mcp2515_read(MCP_CANINTF);
    if (!(intf & 0x01)) { // RX0IF?
        return false;
    }

    // Les ID fra RXB0
    uint8_t sidh = mcp2515_read(0x61); // RXB0SIDH
    uint8_t sidl = mcp2515_read(0x62); // RXB0SIDL
    m_out->id = ((uint16_t)sidh << 3) | (sidl >> 5);

    uint8_t dlc = mcp2515_read(0x65) & 0x0F; // RXB0DLC
    m_out->length = dlc > 8 ? 8 : dlc;

    for (uint8_t i=0; i<m_out->length; i++){
        m_out->data[i] = mcp2515_read(0x66 + i); // RXB0Dn
    }

    // Clear RX0IF
    mcp2515_bit_modify(MCP_CANINTF, 0x01, 0x00);
    return true;


}
