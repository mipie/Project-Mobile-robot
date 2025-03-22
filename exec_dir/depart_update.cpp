/*#define F_CPU 8000000UL
#include "sensor.h"
#include "button.h"
#include "wheel.h"
#include "navigation.h"
#include "timer1.h"
#include "can.h"
#include "led.h"
#include "debug.h"
#include "navigation.h"
#include "communication.h"
#include <avr/io.h>
#include <util/delay.h>
#include "music.h"

const uint8_t DELAI_ANTI_REBOND = 30;

volatile bool interruptPressed = false;
volatile bool whiteButtonPressed = false;
bool isFacingTop = false;



ISR(INT0_vect)
{
    _delay_ms(DELAI_ANTI_REBOND);
    interruptPressed = true;
    EIFR |= (1 << INTF0);
}

ISR(INT1_vect)
{
    _delay_ms(DELAI_ANTI_REBOND);
    whiteButtonPressed = true;
    EIFR |= (1 << INTF1);
}

enum class State
{
    INITIAL,
    DETECTION,
    TRANSMISSION,
    TOP,
    RIGHT, 
    FINDING_POLE,
    POLE_FOUND,
    NO_POLE, 
    TRANSMISSION_FINISH
};

int main()
{
    State state = State::INITIAL; // Doit être dans le main à cause du reset
    Button interruptButton(&DDRD, PD2); // Cavalier en D2, NON-CHANGEABLE
    Button whiteButton(&DDRD, PD3); // Placé en D3, NON-CHANGEABLE
    Led led(&DDRB, &PORTB, PB0, PB1); // Placé en B0/B1, CHANGEABLE
    Music sound; // Placé en D6/D7, le ground du piézo doit être à D6, NON-CHANGEABLE
    interruptButton.startInitialization(INT0, ISC00, ISC01); // Utilise INT0 en D2
    whiteButton.startInitialization(INT1, ISC11, ISC11); // Utilise INT1 en D3
    led.setOff(); // Juste pour être sûr

    while (true) 
    {
        switch (state)
        {
        case State::INITIAL:
            while (state == State::INITIAL) // OK
            {
                if (interruptPressed)
                {
                    state = State::DETECTION;
                    interruptPressed = false;
                }
                if (whiteButtonPressed)
                {
                    state = State::TRANSMISSION;
                    whiteButtonPressed = false;
                }
            }
        case State::DETECTION: // OK
            while (state == State::DETECTION)
            {
                led.setAmber();
                if (interruptPressed)
                {
                    state = State::TOP;
                    interruptPressed = false;
                    led.setOff();
                }
                if (whiteButtonPressed)
                {
                    state = State::RIGHT;
                    whiteButtonPressed = false;
                    led.setOff();
                }
            }
        case State::TOP:
            isFacingTop = true;
            while (state == State::TOP)
            {
                led.setGreen();
                _delay_ms(2000);
                led.setOff();
                _delay_ms(1000);
                // INDIQUE SEULEMENT QUE LE ROBOT EST VERS LE HAUT
                state = State::FINDING_POLE;
            }
        case State::RIGHT:
            isFacingTop = false;
            while (state == State::RIGHT)
            {
                led.setRed();
                _delay_ms(2000);
                led.setOff();
                _delay_ms(1000);
                // SI IL Y A DES ACTIONS SPÉCIALES POUR QUAND IL EST VERS LA DROITE: FAIRE ICI
                state = State::FINDING_POLE;  
            }
        case State::FINDING_POLE:
            while (state == State::FINDING_POLE)
            {
                _delay_ms(2000);
                // LE ROBOT DOIT TROUVER LE POTEAU ICI
                state = State::POLE_FOUND;
                //state = State::NO_POLE;
            }
        case State::POLE_FOUND:
            _delay_ms(100);
            //sound.highPitchSound(); // 3 sons aigus
            while (state == State::POLE_FOUND)
            {
                do
                {
                    for (int i = 0; i < 20; i++)
                    {
                        led.setAmber(); // Led flash ambre à 2Hz
                    }
                    led.setOff();
                    _delay_ms(250);
                } while (!interruptPressed);
                
                if (interruptPressed)
                {
                    state = State::TOP;
                    interruptPressed = false;
                    led.setOff();
                }
            }
        case State::NO_POLE:
            // sound.playnote(sound.defineFrequence(48)); // Le son grave pendant 2s
            // _delay_ms(2000);
            // sound.makePause();
            while (state == State::NO_POLE)
            {
                led.setRedFlash(); // Led flash rouge à 2Hz
                // Le robot ne fait plus rien après (attends le reset)
            }
        case State::TRANSMISSION:
            led.setGreen(); 
            _delay_ms(2000);
            while (state == State::TRANSMISSION)
            {
                led.setGreenFlash(); // Led flash vert à 10Hz
                _delay_ms(2000);
                // FAIRE LA TRANSMISSION ICI
                state = State::TRANSMISSION_FINISH; 
            }
        case State::TRANSMISSION_FINISH:
            led.setOff();
            while (state == State::TRANSMISSION_FINISH)
            {
                // Le robot ne fait plus rien
            }
        }
    }

    return 0;
}*/