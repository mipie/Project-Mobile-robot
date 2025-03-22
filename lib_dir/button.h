/*
* \Noms : Michlove Pierre, Adam Bouhadid, Yacine Barka, Pascale Lafond
* \Description du programme: Cette classe nous permet d'utiliser le bouton au choix
* \Identification du matériel: PINx est utilisé pour le bouton choisi
*/
#pragma once
#ifndef F_CPU
#define F_CPU 8000000L
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

typedef volatile uint8_t *Register;

/*
 * Classe Button:
 *   Le constructeur initialise le Button au choix en mode d'entrée.
 *   La méthode startInitialization enclanche le comportement et
 *   le type d'interruptions causer par le button. La méthode débounce
 *   vient permettre un anti-rebond causé par les plaques présent sur le
 *   le button.
 *
 */

class Button
{
public:
    Button(Register inMode, uint8_t inPin);
    void debounceButton(uint8_t typePauseInteruption);
    void startInitialization(uint8_t typeInteruption, uint8_t firstLevelButton, uint8_t secondLevelButton);

private:
    Register inMode_;
    Register port_;
    const uint8_t inPin_;
};
