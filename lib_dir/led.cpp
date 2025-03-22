#include "led.h"
Led::Led(Registre mode, Registre port, uint8_t pinGreen, uint8_t pinRed) : mode_(mode),
                                                                           port_(port),
                                                                           pinGreen_(pinGreen),
                                                                           pinRed_(pinRed)
{
    *mode_ |= (1 << pinRed) | (1 << pinGreen);
}
void Led::setOff()
{
    *port_ &= (0 << pinGreen_) | (0 << pinRed_);
}
void Led::setGreen()
{
    setOff();
    *port_ |= ((1 << pinGreen_));
}
void Led::setRed()
{
    setOff();
    *port_ |= ((1 << pinRed_));
}
void Led::setAmber()
{
    const uint8_t AMBER_TOGGLE_DELAY = 10;
    setGreen();
    _delay_ms(AMBER_TOGGLE_DELAY);
    setRed();
    _delay_ms(AMBER_TOGGLE_DELAY);
}

void Led::setGreenFlash()
{
    setGreen();
    _delay_ms(50);
    setOff();
    _delay_ms(50);
}

void Led::setRedFlash()
{
    setRed();
    _delay_ms(250);
    setOff();
    _delay_ms(250);
}

void Led::setAmberFlash()
{
    setAmber();
    _delay_ms(250);
    setOff();
    _delay_ms(250);
}
