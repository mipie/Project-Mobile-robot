#include "wheel.h"

Wheel::Wheel()
{
    DDRB |= (1 << PB3) | (1 << PB4);    // PWM
    DDRB |= ((1 << PB1) | (1 << PB2)); // Direction

    TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00);
    TCCR0B |= (1 << CS01);
    TCNT0 = 0;

    setPWMLeft(0);
    setPWMRight(0);
}

void Wheel::setPWMLeft(uint8_t percentage_)
{
    OCR0A = percentage_ * MAX_TIMER_VALUE / MAX_PERCENTAGE_VALUE;
}
void Wheel::setPWMRight(uint8_t percentage_)
{
    OCR0B = 3+ percentage_ * MAX_TIMER_VALUE / MAX_PERCENTAGE_VALUE;
}