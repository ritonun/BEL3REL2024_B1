#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"
#include "dht.h"

int main(void) {
    uint8_t data;

    DDRB |= (1 << PB0);
    PORTB |= (1 << PB0);

    USART_Init(MYUBRR);
    USART_print_str("Setup OK!\r\n");

    while(1) {
        uint16_t temperature, humidity;
        uint8_t a = rcv_data();
        uint8_t b = rcv_data();
        uint8_t c = rcv_data();
        uint8_t d = rcv_data();

        USART_print_str("hum:");
        USART_print_binary(a);
        USART_print_str(", ");
        USART_print_binary(b);
        USART_print_str("\n");
        USART_print_str("temp:");
        USART_print_binary(c);
        USART_print_str(", ");
        USART_print_binary(d);
        USART_print_str("\n");
        _delay_ms(2000);
    }

    return 0;
}