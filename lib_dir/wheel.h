/*
Noms : Michlove Pierre, Adam Bouhadid, Yacine Barka, Pascale Lafond
Classe qui permet d'initialiser le PWM et de faite tourner chacune des roues
séparément grâce à celui-ci.
Identification du matériel: les pins PB1, PB3, PB4 et PB5.
 */ 
#pragma once
#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>



class Wheel
{

public:
    Wheel();//Constructeur, permet  d'initialiser le PWM 
    void setPWMLeft(uint8_t percentage_); //méthode qui active la roue gauche (OC0A)
    void setPWMRight(uint8_t percentage_);//méthode qui active la roue droite (OC0B)

private:
    uint8_t percentage_;
    const uint8_t MAX_TIMER_VALUE = 255;
    const uint8_t MAX_PERCENTAGE_VALUE = 100;  

    


};

