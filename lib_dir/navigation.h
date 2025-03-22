/*
Noms : Michlove Pierre, Adam Bouhadid, Yacine Barka, Pascale Lafond
Classe qui permet de faire bouger le robot dans une direction
spécifiée selon la méthode appelée, grace à la classe wheel.
Identification du matériel: les pins PB1 et PB5.
 */ 
#pragma once
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "wheel.h"

class Navigation
{
public:
    Navigation(); //constructeur, ne fait rien
    void turnLeft(); //méthode qui permet de faire tourner le robot à gauche
    void turnRight();//méthode qui permet de faire tourner le robot à droite
    void moveForward(uint8_t percentage_);//méthode qui permet de faire avancer le robot
    void moveBackward(uint8_t percentage_);//méthopde qui permet de faire reculer le robot
    void turnBack();//méthode qui permet de faire faire un demi-tour au robot
    void turnOff();//méthode qui permet d'arreter les roues du robot
private:
    Wheel wheel_;
    uint8_t percentage_;
    const uint8_t fullPercentage = 100;
    const uint8_t lowPercentage = 30;
    const uint8_t mediumPercentage = 60;
};

