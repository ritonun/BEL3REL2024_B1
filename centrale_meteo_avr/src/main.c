#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"

int main(void) {
    char serialCharacter;
    DDRB |= (1 << PB5);

    USART_Init(MYUBRR);
    //initUSART();
    USART_print_str("Hello World!\r\n");

    while(1) {
        // USART_print_str("new com\r\n");
        /*
        PORTB = (1 << PB5);
        _delay_ms(1000);
        PORTB = 0x00;
        _delay_ms(1000);
        */
    }
}