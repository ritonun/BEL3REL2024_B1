#include <avr/io.h>
#include <util/delay.h>

#include "dht.h"

#define DHT_PORT PORTB
#define DHT_DDR DDRB
#define DHT_PIN PB0

void request() {
    DHT_DDR |= (1 << DHT_PIN);
    DHT_PORT &= ~(1 << DHT_PIN);
    _delay_ms(20);
    DHT_PORT |= (1 << DHT_PIN);
}

void response() {
    DHT_DDR &= ~(1 << DHT_PIN);
    while(DHT_PORT & (1<<DHT_PIN));
    while((DHT_PORT & (1<<DHT_PIN))==0);
    while(DHT_PORT & (1<<DHT_PIN));
}

uint8_t rcv_data() {   
    uint8_t c = 0;
    for (int q=0; q<8; q++)
    {
        while((DHT_PORT & (1 << DHT_PIN)) == 0);  /* check received bit 0 or 1 */
        _delay_us(30);
        if(DHT_PORT & (1 << DHT_PIN))/* if high pulse is greater than 30ms */
        c = (c<<1)|(0x01);  /* then its logic HIGH */
        else            /* otherwise its logic LOW */
        c = (c<<1);
        while(DHT_PORT & (1<<DHT_PIN));
    }
    return c;
}