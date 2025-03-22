/*
Noms : Michlove Pierre, Adam Bouhadid, Yacine Barka, Pascale Lafond
Classe qui permet  de facilier l'utilisation de la led sur le robot
dentification du matériel: PINx est utilisé pour la led
 */ 
 
#pragma once
#ifndef LED_H
#define LED_H
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>


typedef volatile uint8_t* Registre;

class Led
{
public:
    Led(Registre mode, Registre port, uint8_t pinGreen, uint8_t pinRed); //constructeur initialise la led en prenant comme parametre le mode, port, ainsi que les pin que l'on veut utiliser pour la lumiere rouge et verte.

    void setGreen(); //Methode qui permet de changer la couleur de la led a vert.
    void setRed();//Methode qui permet de changer la couleur de la led a rouge.
    void setOff(); //Permet d'eteindre la del afin ne plus afficher de couleur
    void setAmber(); //Methode qui permet de changer la couleur de la led a ambre.
    void setGreenFlash();
    void setRedFlash();
    void setAmberFlash();

private:

    Registre mode_;
    Registre port_;
    const uint8_t pinGreen_;
    const uint8_t pinRed_;
};
#endif
