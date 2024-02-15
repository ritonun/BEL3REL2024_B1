#include <avr/io.h>
#include "time.h"

int main(void) {
    DDRB |= (1 << PB5);

    while(1) {
        PORTB = (1 << PB5);
        wait(1000);
        PORTB = 0x00;
        wait(1000);
    }

}