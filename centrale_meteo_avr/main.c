#include <avr/io.h>
#include <avr/interrupt.h>

ISR(TIMER1_OVF_vect) {
    // fonction execute lors de l'interruptions
    PORTB ^= _BV(PORTB5);   // _BV correspond a: (1 << n)
    TCNT1 = 65535 - (F_CPU/1024);   // remet le counter a 0
}

int main(void) {
    /* SETUP */
    DDRB = DDRB | (1 << DDB5);


    /* TIMER */
    // max value of 65535
    TCNT1 = 65535 - (F_CPU/1024);   // TCNT1: Timer 1
    // set prescaler a 1024
    // clock rate: 16M/1024 = 15625Hz
    TCCR1B = (1 << CS10) | (1 << CS12);
    TCCR1A = 0x00;  // mode de fonctionnement normal
    TIMSK1 = (1 << TOIE1);  // set le flag pour activer les interrput lors du timer ovrflow

    sei();  // activer les interruptions global

    /* LOOP */
    while(1) {

    }
}