/*
* \Noms : Michlove Pierre, Adam Bouhadid, Yacine Barka, Pascale Lafond
* \Description du programme: Cette classe nous permet d'utiliser le capteur de lumière
* \Identification du matériel: PINx est utilisé pour relier le capteur et la led. 
*/
#include "sensor.h"

Led led(&DDRB,&PORTB, PB0, PB1);

Sensor::Sensor()
{
}

uint16_t Sensor::read16Bits()
{
   
    return (myCan_.lecture(2) >> 2);
}

void Sensor::detectLowLightTurnGreen()
{
    
    if (read16Bits() < LIGHT_INTENSITY_LOW_)
    {
        led.setGreen();
    }
}

void Sensor::detectMidLightTurnAmber()
{
    if (read16Bits() > LIGHT_INTENSITY_LOW_ && read16Bits() < LIGHT_INTENSITY_MID_)
    {
        led.setAmber();
    }
}

void Sensor::detectHighLightTurnRed()
{
    if (read16Bits() > LIGHT_INTENSITY_MID_)
    {
        led.setRed();
    }
}
