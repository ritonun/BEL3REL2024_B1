#include <avr/io.h>
#include "usart.h"
#include <util/setbaud.h>

void USART_Init(unsigned int ubrr) {
    // Init le baud rate
    UBRR0H = UBRRH_VALUE;                   
    UBRR0L = UBRRL_VALUE;

    // activer le recepteur et transmitteur
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // format de la frame (8bit , 1 stop bit)
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  
}

void USART_tx_byte(uint8_t data) {
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}

void USART_print_str(const char str[]) {
    uint8_t i = 0;
    while(str[i]) {
        USART_tx_byte(str[i]);
        i++;
    }
}