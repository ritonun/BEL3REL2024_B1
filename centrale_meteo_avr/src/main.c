#include <avr/io.h>
#include <util/delay.h>

#include "usart.h"

int main(void) {
    uint8_t data;
    DDRB |= (1 << PB5);

    USART_Init(MYUBRR);
    USART_print_str("Setup OK!\r\n");

    while(1) {
        data = USART_rx_byte();
        USART_tx_byte(data);
        USART_print_str((const char)data);
        USART_print_str("\r\n");
    }

    return 0;
}