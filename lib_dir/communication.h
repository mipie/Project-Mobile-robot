/*
Noms : Michlove Pierre, Adam Bouhadid, Yacine Barka, Pascale Lafond
Classe qui permet l'utilisation du module UART du microcontroleur
dentification du matériel: Utilise le registre UDR0 ainsi que le registre UCSR0
 */ 
#pragma once
#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#endif
#include <avr/io.h> 
#include "memoire_24.h"
#include <avr/interrupt.h>

class Communication{

public:
    Communication(); //Constructeur sans parametres pour pouvoir initialiser la classe
    void transmissionUART(uint8_t data); //Methode qui prend un parametre un entier non signe et l'envoie sur le port du module UART
    void initialisationUART(); //Permet l'initialisation du module UART avec des vitesses et trames specifique
    uint8_t readUART(); // Methode qui permet lire les donne recu par le module UART et retourner cette donnee.
    void sendMessage(const char* word); //Methode qui lit la valeur contenu a l'adresse entree en parametre et qui l'affiche
    
};