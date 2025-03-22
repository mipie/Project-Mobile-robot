/*
Noms : Michlove Pierre, Adam Bouhadid, Yacine Barka, Pascale Lafond
Classe qui permet de configurer un timer avec la méthode startTimer
qui utilise le timer 1 de la carte 
 */ 
#pragma once
#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


class Timer
{
public:
    Timer(); // Constructeur: ne fait rien
    void startTimer(uint16_t time, uint8_t mode); // Méthode qui démarre le timer avec la valeur de comparaison "time"
private:
//Aucune données conservées//
};