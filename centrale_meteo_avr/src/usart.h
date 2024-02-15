#ifndef USART_H
#define USART_H

#define FOSC 16000000           // frequence systeme
#define BAUD 9600             // baud rate
#define MYUBRR FOSC/16/BAUD-1   // valeur registre UBBR (calculer seon la doc)

void USART_Init(unsigned int ubrr);

void USART_tx_byte(uint8_t data);
uint8_t USART_rx_byte();

void USART_print_str(const char str[]);
void USART_print_binary(uint8_t byte);

#endif