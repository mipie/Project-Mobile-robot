/*
* \Noms : Michlove Pierre, Adam Bouhadid, Yacine Barka, Pascale Lafond
* \Description du programme: Cette classe nous permet d'utiliser le capteur de lumière
* \Identification du matériel: PINx est utilisé pour relier le capteur et la led. 
*/
#pragma once
#ifndef SENSOR_h
#define SENSOR_h
#define F_CPU 8000000UL
#include <avr/io.h>
#include "can.h"
#include "led.h"

/*
 * Classe Sensor:
 *   Le constructeur initialise le Sensor.
 *   La méthode read8bits permet de lire en bit les données recueillie par le
 *   capteur. Les trois méthodes suivantes nous permet d'allumer la led selon 
 *   l'intensité de la lumière lu par la méthode read8bits.
 *   
 *
 */

class Sensor
{
public:
    Sensor();
    uint16_t read16Bits();
    void detectLowLightTurnGreen();
    void detectMidLightTurnAmber();
    void detectHighLightTurnRed();

private:
    const uint8_t LIGHT_INTENSITY_LOW_ = 150;
    const uint8_t LIGHT_INTENSITY_MID_ = 240;
    can myCan_;
};

#endif