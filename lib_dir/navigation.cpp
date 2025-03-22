#include "navigation.h"


Navigation::Navigation()
{
}


void Navigation::moveForward(uint8_t percentage_)
{
   
    PORTB &= ~((1 << PB1) | (1 << PB2));
    wheel_.setPWMLeft(percentage_);
    wheel_.setPWMRight(percentage_-2);
}


void Navigation::moveBackward(uint8_t percentage_)
{   
    const uint8_t delay = 200;
    PORTB &= ~((1 << PB1) | (1 << PB2));
    _delay_ms(delay);
    PORTB |= ((1 << PB1) | (1 << PB2));
    wheel_.setPWMLeft(percentage_);
    wheel_.setPWMRight(percentage_);
}


void Navigation::turnLeft()
{
    const uint8_t delay = 200;
    PORTB |= ((1 << PB1));
    PORTB &= ~((1 << PB2));
    _delay_ms(delay);
    PORTB &= ~((1 << PB1));
    PORTB |= ((1 << PB2));
    wheel_.setPWMLeft(80);
    wheel_.setPWMRight(75);
}


void Navigation::turnRight()
{
    const uint8_t delay = 200;
    PORTB |= ((1 << PB2));
    PORTB &= ~((1 << PB1));
    _delay_ms(delay);
    PORTB &= ~((1 << PB2));
    PORTB |= ((1 << PB1));
    wheel_.setPWMLeft(80);
    wheel_.setPWMRight(75);
}


void Navigation::turnBack()
{
    const uint8_t delay = 200;
    PORTB |= ((1 << PB1) | (1 << PB2));
    _delay_ms(delay);
    PORTB &= ~((1 << PB1) | (1 << PB2));
    wheel_.setPWMLeft(0);
    wheel_.setPWMRight(fullPercentage);
}


void Navigation::turnOff()
{
    wheel_.setPWMLeft(0);
    wheel_.setPWMRight(0);
}