
#define F_CPU 4915200UL
#include "can.h"
#include "util/delay.h"


void can_init(){
    mcp2515_reset();
    _delay_ms(50);
    uint8_t config_mode = 0b10000000;
    uint8_t loopback_mode = 0b01000000;
    uint8_t normal_mode = 0b00000000;

    uint8_t rx_interrupt = 0x03;
    uint8_t loopback_flag = 0x03;

   // mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, loopback_mode); // CanControll register  - lopopback  mode
   // mcp2515_bit_modify(MCP_CANSTAT, MODE_MASK, loopback_mode); // CanStatus register - lopopback  mode

    mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, config_mode); // CanControll register - config mode
    mcp2515_bit_modify(MCP_CANSTAT, MODE_MASK, config_mode); // CanStatus register - config mode

 //   mcp2515_bit_modify(MCP_CANINTE, loopback_interrupt, );

    while (( config_mode & MODE_MASK ) != MODE_CONFIG ) { ;}

    // skrive til CNF registre
    // TQ=16, sampler 75% som er 12
    mcp2515_write(MCP_CNF1, 0x00); // sett BRP=0 og SWJ= 1*TQ (00),
      
    mcp2515_write(MCP_CNF2, 0b10111010); // sett BLTMODE=1 og SAMPLE_1X=0, PS1 bit length  = 111 (7 slik at vi får 8), prop_seg bit length =010 (2 slik at vi får 3)

    mcp2515_write(MCP_CNF3, 0x03); // SOF_DISABLE = 0, WAKFIL_DISABLE= 0, 000, PS2 bit lengde= 011 (3 slik at vi får 4)


    mcp2515_bit_modify(MCP_CANINTF, 0xFF, 0x00); //rydder flagg, alle mask lik 1 og flag = 0
    mcp2515_write(MCP_CANINTE, rx_interrupt); // enable rx interrupts
    
    mcp2515_bit_modify(MCP_CANCTRL, MODE_MASK, normal_mode); // CanControll register - normal mode
    mcp2515_bit_modify(MCP_CANSTAT, MODE_MASK, normal_mode); // CanStatus register - normal mode
    
    
    while (( normal_mode & MODE_MASK ) != MODE_NORMAL ) { ;}

}




void can_message_send(can_message *message){
    uint8_t pending_buffer = mcp2515_read(MCP_TXB0CTRL); // control register 
    while(pending_buffer & (1 << 3)){ //request-to-send 0
    };
    uint8_t sid31 = ((message->id) >> 3) & 0xFF; //first seven
    uint8_t sid32 = ((message->id) & 0x07) << 5; //rest 3

    mcp2515_write(0x31, sid31);
    mcp2515_write(0x32, sid32); // id
    
    mcp2515_write(0x35, (message->length & 0x0F)); //length

    for (uint8_t i = 0; i < message->length; i++){ // skrive data
        mcp2515_write(0x36 + i, message->data[i]);
    }

    mcp2515_request_to_send(0x01); // buffer 0

}

bool can_message_receive(can_message *message){ 
    uint8_t intf = mcp2515_read(MCP_CANINTF); //interrupt flag

    if (!(intf & 0x01)) { // must be cleared to allow new message
        return false;
    }

    // identider bits
    uint8_t sid61 = mcp2515_read(MCP_RXB0SIDH); // RXB0SIDH 0x61
    uint8_t sid62 = mcp2515_read(0x62); // RXB0SIDL

    message->id = (sid61 << 3) | (sid62 >> 5);

    // message length
    uint8_t length65 = mcp2515_read(0x65);
    if(length65 > 8){
        message->length = 8;
    } else{
        message->length = length65;
    }

    //message data
    for (uint8_t i=0; i< message->length; i++){
        message->data[i] = mcp2515_read(0x66 + i); 
    }

    // Clear interrupt flag
    mcp2515_bit_modify(MCP_CANINTF, 0x01, 0x00);
    return true;


}
