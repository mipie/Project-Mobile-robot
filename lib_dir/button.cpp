/*
 * \Noms : Michlove Pierre, Adam Bouhadid, Yacine Barka, Pascale Lafond
 * \Description du programme: Cette classe nous permet d'utiliser le bouton au choix
 * \Identification du matériel: PINx est utilisé pour le bouton choisi
 */
#include "button.h"

Button::Button(Register inMode, uint8_t inPin) : inMode_(inMode),
                                                 inPin_(inPin)
{
    *inMode_ &= ~(1 << inPin);
}

void Button::startInitialization(uint8_t typeInteruption, uint8_t firstLevelButton, uint8_t secondLevelButton)
{
    // cli est une routine qui bloque toutes les interruptions.
    cli();
    // configurer et choisir les ports pour les entrées
    // et les sorties.
    DDRA |= (1 << PA2) | (1 << PA3);

    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << typeInteruption);

    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << firstLevelButton) | (1 << secondLevelButton);

    // sei permet de recevoir à nouveau des interruptions.
    sei();
}

void Button::debounceButton(uint8_t typeOfPauseInterruption)
{
    // laisser un délai avant de confirmer la réponse du
    // bouton-poussoir:
    const uint8_t DEBOUNCE_DELAY_ = 30;
    _delay_ms(DEBOUNCE_DELAY_);

    // Ce souvient des interruption pour les exécuter après la première
    // interruption executer
    EIFR |= (1 << typeOfPauseInterruption);
}
