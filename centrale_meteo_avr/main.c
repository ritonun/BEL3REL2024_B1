#include <avr/io.h>

void TWI_init_master(void) // Function to initialize master
{
    TWBR=0x01;    // Bit rate
    TWSR=(0<<TWPS1)|(0<<TWPS0);    // Setting prescalar bits
    // SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
}