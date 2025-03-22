#define F_CPU 8000000UL
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
#include "point.h"

Navigation nav;
volatile bool detected = false;
bool dist = false, vu = false;
can cann;
uint8_t counter = 0, val = 0, memWrited = 0;
Point coord(0, 0);
Communication com;
Memoire24CXXX mem;
uint8_t adr = 0x00;
Button interruptButton(&DDRD, PD2); // Cavalier en D2, NON-CHANGEABLE
Button whiteButton(&DDRD, PD3);     // Placé en D3, NON-CHANGEABLE
Led led(&DDRC, &PORTC, PC6, PC7);   // Placé en C0/C1, CHANGEABLE
Music sound;                        // Placé en D6/D7, le ground du piézo doit être à D6, NON-CHANGEABLE

void initialisationUART(void)
{

    // 2400 bauds. Nous vous donnons la valeur des deux

    // premiers registres pour vous éviter des complications.

    UBRR0H |= 0;

    UBRR0L |= 0xCF;

    // permettre la réception et la transmission par le UART0

    UCSR0A |= 0;

    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    // Format des trames: 8 bits, 1 stop bits, sans parité

    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}
void transmissionUART(uint8_t data)
{

    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = data;
}

void turnLeft45()
{
    nav.turnRight();
    _delay_ms(400);
    nav.turnOff();
    _delay_ms(1000);
}

void turnRight45()
{
    nav.turnLeft();
    _delay_ms(400);
    nav.turnOff();
    _delay_ms(1000);
}

void unPeuD()
{
    nav.turnLeft();
    _delay_ms(200);
    nav.turnOff();
    _delay_ms(1000);
}

void unPeuG()
{
    nav.turnRight();
    _delay_ms(220);
    nav.turnOff();
    _delay_ms(1000);
}

void miniD()
{
    nav.turnLeft();
    _delay_ms(100);
    nav.turnOff();
    _delay_ms(300);
}

void miniG()
{
    nav.turnRight();
    _delay_ms(100);
    nav.turnOff();
    _delay_ms(300);
}

uint8_t detecteur()
{
    uint16_t a = 0;
    uint16_t b = 0;
    for (uint8_t i = 0; i < 30; i++)
    {
        a = a + (cann.lecture(PA0) >> 2);
   }
    b = a/30;
    return b;
}

void north(Point coord, bool dist)
{
    if (dist)
    {
        coord.moveInFront(coord);
    }
    else
    {
        coord.moveInFront(coord);
        coord.moveInFront(coord);
    }
}

void northE(Point coord, bool dist)
{

    if (dist)
    {
        coord.moveInFront(coord);
        coord.moveRight(coord);
    }
    else
    {
        coord.moveInFront(coord);
        coord.moveRight(coord);
        coord.moveInFront(coord);
        coord.moveRight(coord);
    }
}

void east(Point coord, bool dist)
{

    if (dist)
    {
        coord.moveRight(coord);
    }
    else
    {
        coord.moveRight(coord);
        coord.moveRight(coord);
    }
}

void southE(Point coord, bool dist)
{

    if (dist)
    {
        coord.moveRight(coord);
        coord.moveBack(coord);
    }
    else
    {
        coord.moveRight(coord);
        coord.moveBack(coord);
        coord.moveRight(coord);
        coord.moveBack(coord);
    }
}

void south(Point coord, bool dist)
{
    if (dist)
    {
        coord.moveBack(coord);
    }
    else
    {
        coord.moveBack(coord);
        coord.moveBack(coord);
    }
}

void southW(Point coord, bool dist)
{
    if (dist)
    {
        coord.moveBack(coord);
        coord.moveLeft(coord);
    }
    else
    {
        coord.moveBack(coord);
        coord.moveLeft(coord);
        coord.moveBack(coord);
        coord.moveLeft(coord);
    }
}

void west(Point coord, bool dist)
{

    if (dist)
    {
        coord.moveLeft(coord);
    }
    else
    {
        coord.moveLeft(coord);
        coord.moveLeft(coord);
    }
}

void northW(Point coord, bool dist)
{

    if (dist)
    {
        coord.moveInFront(coord);
        coord.moveLeft(coord);
    }
    else
    {
        coord.moveInFront(coord);
        coord.moveLeft(coord);
        coord.moveInFront(coord);
        coord.moveLeft(coord);
    }
}

void detectionD()
{
    counter = 0;
    while (!detected)
    {
        val = detecteur(); // On enleve les 2 bits les moins significatif
        if (val > 25)
        {
            detected = true;
            break;
        }

        turnRight45();
        counter++;
        val = detecteur();

        if (val > 25)
        {
            detected = true;
            break;
        }

        
        unPeuG();
        val = detecteur();

        if (val > 25)
        {
            detected = true;
            break;
        }

        uint8_t cpt =0;
        bool a=false;
        while (cpt<5)
        {
            
        miniD();
        val = detecteur();

        if (val > 25)
        {
            detected = true;
            a=true;
            break;
        }
        cpt++;
        }

        if (a)
        {
            break;
        }
        
        if (counter > 7)
        {
            detected = false;
            break;
        }
    }
}

void detectionG()
{
    counter = 0;
    while (!detected)
    {
        val = detecteur();
        if (val > 25)
        {
            detected = true;
            break;
        }

        turnLeft45();
        counter++;
        val = detecteur();

        if (val > 25)
        {
            detected = true;
            break;
        }

        unPeuG();
        val = detecteur();
        if (val > 25)
        {
            detected = true;
            break;
        }

        uint8_t cpt =0;
        bool a=false;
        while (cpt<5)
        {
            
        miniD();
        val = detecteur();

        if (val > 25)
        {
            detected = true;
            a=true;
            break;
        }
        cpt++;
        }

        if (a)
        {
            break;
        }

        if (counter > 7)
        {
            detected = false;
            break;
        }
    }
}

void moveIfHere()
{
    uint8_t a = 1;
    while (detected)
    {
        val = detecteur();

        if (vu && val < 25)
        {
            nav.turnOff();
            while (vu)
            {         
            
            uint8_t cpt = 0;
            while (true)
            {
                miniD();
                val = detecteur();
                if (val > 24)
                {
                    vu = false;
                    break;
                }
                cpt++;
                if (cpt > (a))
                {
                    break;
                }
            }
            cpt = 0;
            while (true)
            {
                miniG();
                val = detecteur();
                if (val > 24)
                {
                    vu = false;
                    break;
                }
                cpt++;
                if (cpt > (a + 1))
                {
                    break;
                }
            }
            a++;
        }
        }

        if (val >= 25 && val < 30)
        {
            nav.moveForward(50);
            _delay_ms(700);
            vu = true;
            val = detecteur();
        }

        val = detecteur();

        if (val >= 30 && val < 90)
        {

            nav.moveForward(50);
            vu = true;

            val = detecteur();
        }

        val = detecteur();
        if (val >= 90)
        {

            detected = false;
            nav.turnOff();
            val = detecteur();
        }
    }
}

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

volatile bool soundOn = false;

ISR(TIMER2_COMPA_vect)
{
    if (soundOn)
    {
        PORTA = (0 << PA5);
        soundOn = false;
    }
    else
    {
        PORTA = (1 << PA5);
        soundOn = true;
    }
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
    DDRA |= (1 << PA5) | (1 << PA4);
    PORTA = (0 << PA4);
    interruptButton.startInitialization(INT0, ISC00, ISC01); // Utilise INT0 en D2
    whiteButton.startInitialization(INT1, ISC11, ISC11);     // Utilise INT1 en D3
    led.setOff();
    initialisationUART();

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
                detectionD();
                dist = false;
                if (val > 40)
                {
                    dist = true;
                }
                moveIfHere();
                switch (counter)
                {
                case 0:
                    //north(coord, dist);
                    // coord.moveInFront(coord);
                    if (dist)
                    {
                        coord.moveInFront(coord);
                    }
                    else
                    {
                        coord.moveInFront(coord);
                        coord.moveInFront(coord);
                    }
                    
                    state = State::POLE_FOUND;
                    break;
                case 1:
                    // northE(coord, dist);
                    if (dist)
                    {
                        coord.moveInFront(coord);
                        coord.moveRight(coord);
                    }
                    else
                    {
                        coord.moveInFront(coord);
                        coord.moveRight(coord);
                        coord.moveInFront(coord);
                        coord.moveRight(coord);
                    }
                    
                    state = State::POLE_FOUND;
                    break;
                case 2:
                    // east(coord, dist);
                    if (dist)
                    {
                        coord.moveRight(coord);
                    }
                    else
                    {
                        coord.moveRight(coord);
                        coord.moveRight(coord);
                    }
                    
                    state = State::POLE_FOUND;
                    break;
                default:
                    state = State::NO_POLE;
                    break;
                }
            }
            break;
        case State::RIGHT:
            isFacingTop = false;
            while (state == State::RIGHT)
            {
                led.setRed();
                _delay_ms(2000);
                led.setOff();
                _delay_ms(1000);
                // SI IL Y A DES ACTIONS SPÉCIALES POUR QUAND IL EST VERS LA DROITE: FAIRE ICI
                detectionG();
                dist = false;
                if (val > 40)
                {
                    dist = true;
                }
                moveIfHere();
                switch (counter)
                {
                case 0:
                    // east(coord, dist);
                    if (dist)
                    {
                        coord.moveRight(coord);
                    }
                    else
                    {
                        coord.moveRight(coord);
                        coord.moveRight(coord);
                    }
                    coord.moveBack(coord);
                    state = State::POLE_FOUND;
                    break;
                case 1:
                    // northE(coord, dist);
                    if (dist)
                    {
                        coord.moveInFront(coord);
                        coord.moveRight(coord);
                    }
                    else
                    {
                        coord.moveInFront(coord);
                        coord.moveRight(coord);
                        coord.moveInFront(coord);
                        coord.moveRight(coord);
                    }
                    coord.moveBack(coord);
                    state = State::POLE_FOUND;
                    break;
                case 2:
                    // north(coord, dist);
                    if (dist)
                    {
                        coord.moveInFront(coord);
                    }
                    else
                    {
                        coord.moveInFront(coord);
                        coord.moveInFront(coord);
                    }
                    coord.moveBack(coord);
                    state = State::POLE_FOUND;
                    break;
                default:
                    state = State::NO_POLE;
                    break;
                }
                state = State::FINDING_POLE;
            }
            break;
        case State::FINDING_POLE:
            while (state == State::FINDING_POLE)
            {
                _delay_ms(2000);
                // LE ROBOT DOIT TROUVER LE POTEAU ICI

                if (coord.getPointX() == 7 && coord.getPointY() == 0)
                {

                    detectionG();
                    dist = false;
                    if (val > 40)
                    {
                        dist = true;
                    }
                    moveIfHere();
                    switch (counter)
                    {
                    case 0:
                        // north(coord, dist);
                        if (dist)
                        {
                            coord.moveInFront(coord);
                        }
                        else
                        {
                            coord.moveInFront(coord);
                            coord.moveInFront(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 1:
                        // northW(coord, dist);
                        if (dist)
                        {
                            coord.moveInFront(coord);
                            coord.moveLeft(coord);
                        }
                        else
                        {
                            coord.moveInFront(coord);
                            coord.moveLeft(coord);
                            coord.moveInFront(coord);
                            coord.moveLeft(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 2:
                        // west(coord, dist);
                        if (dist)
                        {
                            coord.moveLeft(coord);
                        }
                        else
                        {
                            coord.moveLeft(coord);
                            coord.moveLeft(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 3:
                        // southW(coord, dist);
                        if (dist)
                        {
                            coord.moveBack(coord);
                            coord.moveLeft(coord);
                        }
                        else
                        {
                            coord.moveBack(coord);
                            coord.moveLeft(coord);
                            coord.moveBack(coord);
                            coord.moveLeft(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 4:
                        // south(coord, dist);
                        if (dist)
                        {
                            coord.moveBack(coord);
                        }
                        else
                        {
                            coord.moveBack(coord);
                            coord.moveBack(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 5:
                        // southE(coord, dist);
                        if (dist)
                        {
                            coord.moveRight(coord);
                            coord.moveBack(coord);
                        }
                        else
                        {
                            coord.moveRight(coord);
                            coord.moveBack(coord);
                            coord.moveRight(coord);
                            coord.moveBack(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 6:
                        // east(coord, dist);
                        if (dist)
                        {
                            coord.moveRight(coord);
                        }
                        else
                        {
                            coord.moveRight(coord);
                            coord.moveRight(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 7:
                        // northE(coord, dist);
                        if (dist)
                        {
                            coord.moveInFront(coord);
                            coord.moveRight(coord);
                        }
                        else
                        {
                            coord.moveInFront(coord);
                            coord.moveRight(coord);
                            coord.moveInFront(coord);
                            coord.moveRight(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    default:
                        state = State::NO_POLE;
                        break;
                    }
                }
                else if (coord.getPointX() == 7 && coord.getPointY() == 1)
                {
                    detectionG();
                    dist = false;
                    if (val > 40)
                    {
                        dist = true;
                    }
                    moveIfHere();
                    switch (counter)
                    {
                    case 0:
                        // north(coord, dist);
                        if (dist)
                        {
                            coord.moveInFront(coord);
                        }
                        else
                        {
                            coord.moveInFront(coord);
                            coord.moveInFront(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 1:
                        // northW(coord, dist);
                        if (dist)
                        {
                            coord.moveInFront(coord);
                            coord.moveLeft(coord);
                        }
                        else
                        {
                            coord.moveInFront(coord);
                            coord.moveLeft(coord);
                            coord.moveInFront(coord);
                            coord.moveLeft(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 2:
                        // west(coord, dist);
                        if (dist)
                        {
                            coord.moveLeft(coord);
                        }
                        else
                        {
                            coord.moveLeft(coord);
                            coord.moveLeft(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 3:
                        // southW(coord, dist);
                        if (dist)
                        {
                            coord.moveBack(coord);
                            coord.moveLeft(coord);
                        }
                        else
                        {
                            coord.moveBack(coord);
                            coord.moveLeft(coord);
                            coord.moveBack(coord);
                            coord.moveLeft(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 4:
                        // south(coord, dist);
                        if (dist)
                        {
                            coord.moveBack(coord);
                        }
                        else
                        {
                            coord.moveBack(coord);
                            coord.moveBack(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 5:
                        // southE(coord, dist);
                        if (dist)
                        {
                            coord.moveRight(coord);
                            coord.moveBack(coord);
                        }
                        else
                        {
                            coord.moveRight(coord);
                            coord.moveBack(coord);
                            coord.moveRight(coord);
                            coord.moveBack(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 6:
                        // east(coord, dist);
                        if (dist)
                        {
                            coord.moveRight(coord);
                        }
                        else
                        {
                            coord.moveRight(coord);
                            coord.moveRight(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 7:
                        // northE(coord, dist);
                        if (dist)
                        {
                            coord.moveInFront(coord);
                            coord.moveRight(coord);
                        }
                        else
                        {
                            coord.moveInFront(coord);
                            coord.moveRight(coord);
                            coord.moveInFront(coord);
                            coord.moveRight(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    default:
                        state = State::NO_POLE;
                        break;
                    }
                }
                else if (coord.getPointX() == 7 && coord.getPointY() == 2)
                {
                    detectionG();
                    dist = false;
                    if (val > 40)
                    {
                        dist = true;
                    }
                    moveIfHere();
                    switch (counter)
                    {
                    case 0:
                        // north(coord, dist);
                        if (dist)
                        {
                            coord.moveInFront(coord);
                        }
                        else
                        {
                            coord.moveInFront(coord);
                            coord.moveInFront(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 1:
                        // northW(coord, dist);
                        if (dist)
                        {
                            coord.moveInFront(coord);
                            coord.moveLeft(coord);
                        }
                        else
                        {
                            coord.moveInFront(coord);
                            coord.moveLeft(coord);
                            coord.moveInFront(coord);
                            coord.moveLeft(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 2:
                        // west(coord, dist);
                        if (dist)
                        {
                            coord.moveLeft(coord);
                        }
                        else
                        {
                            coord.moveLeft(coord);
                            coord.moveLeft(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 3:
                        // southW(coord, dist);
                        if (dist)
                        {
                            coord.moveBack(coord);
                            coord.moveLeft(coord);
                        }
                        else
                        {
                            coord.moveBack(coord);
                            coord.moveLeft(coord);
                            coord.moveBack(coord);
                            coord.moveLeft(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 4:
                        // south(coord, dist);
                        if (dist)
                        {
                            coord.moveBack(coord);
                        }
                        else
                        {
                            coord.moveBack(coord);
                            coord.moveBack(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 5:
                        // southE(coord, dist);
                        if (dist)
                        {
                            coord.moveRight(coord);
                            coord.moveBack(coord);
                        }
                        else
                        {
                            coord.moveRight(coord);
                            coord.moveBack(coord);
                            coord.moveRight(coord);
                            coord.moveBack(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 6:
                        // east(coord, dist);
                        if (dist)
                        {
                            coord.moveRight(coord);
                        }
                        else
                        {
                            coord.moveRight(coord);
                            coord.moveRight(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 7:
                        // northE(coord, dist);
                        if (dist)
                        {
                            coord.moveInFront(coord);
                            coord.moveRight(coord);
                        }
                        else
                        {
                            coord.moveInFront(coord);
                            coord.moveRight(coord);
                            coord.moveInFront(coord);
                            coord.moveRight(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    default:
                        state = State::NO_POLE;
                        break;
                    }
                }
                else if (coord.getPointX() == 7 && coord.getPointY() == 3)
                {
                    detectionG();
                    dist = false;
                    if (val > 40)
                    {
                        dist = true;
                    }
                    moveIfHere();
                    switch (counter)
                    {
                    case 0:
                        // north(coord, dist);
                        if (dist)
                        {
                            coord.moveInFront(coord);
                        }
                        else
                        {
                            coord.moveInFront(coord);
                            coord.moveInFront(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 1:
                        // northW(coord, dist);
                        if (dist)
                        {
                            coord.moveInFront(coord);
                            coord.moveLeft(coord);
                        }
                        else
                        {
                            coord.moveInFront(coord);
                            coord.moveLeft(coord);
                            coord.moveInFront(coord);
                            coord.moveLeft(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 2:
                        // west(coord, dist);
                        if (dist)
                        {
                            coord.moveLeft(coord);
                        }
                        else
                        {
                            coord.moveLeft(coord);
                            coord.moveLeft(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 3:
                        // southW(coord, dist);
                        if (dist)
                        {
                            coord.moveBack(coord);
                            coord.moveLeft(coord);
                        }
                        else
                        {
                            coord.moveBack(coord);
                            coord.moveLeft(coord);
                            coord.moveBack(coord);
                            coord.moveLeft(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 4:
                        // south(coord, dist);
                        if (dist)
                        {
                            coord.moveBack(coord);
                        }
                        else
                        {
                            coord.moveBack(coord);
                            coord.moveBack(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 5:
                        // southE(coord, dist);
                        if (dist)
                        {
                            coord.moveRight(coord);
                            coord.moveBack(coord);
                        }
                        else
                        {
                            coord.moveRight(coord);
                            coord.moveBack(coord);
                            coord.moveRight(coord);
                            coord.moveBack(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 6:
                        // east(coord, dist);
                        if (dist)
                        {
                            coord.moveRight(coord);
                        }
                        else
                        {
                            coord.moveRight(coord);
                            coord.moveRight(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 7:
                        // northE(coord, dist);
                        if (dist)
                        {
                            coord.moveInFront(coord);
                            coord.moveRight(coord);
                        }
                        else
                        {
                            coord.moveInFront(coord);
                            coord.moveRight(coord);
                            coord.moveInFront(coord);
                            coord.moveRight(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    default:
                        state = State::NO_POLE;
                        break;
                    }
                }
                else
                {
                    detectionD();
                    dist = false;
                    if (val > 40)
                    {
                        dist = true;
                    }
                    moveIfHere();
                    switch (counter)
                    {
                    case 0:
                        north(coord, dist);
                        // coord.moveInFront(coord);
                        if (dist)
                        {
                            coord.moveInFront(coord);
                        }
                        else
                        {
                            coord.moveInFront(coord);
                            coord.moveInFront(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 1:
                        // northE(coord, dist);
                        if (dist)
                        {
                            coord.moveInFront(coord);
                            coord.moveRight(coord);
                        }
                        else
                        {
                            coord.moveInFront(coord);
                            coord.moveRight(coord);
                            coord.moveInFront(coord);
                            coord.moveRight(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 2:
                        // east(coord, dist);
                        if (dist)
                        {
                            coord.moveRight(coord);
                        }
                        else
                        {
                            coord.moveRight(coord);
                            coord.moveRight(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 3:
                        // southE(coord, dist);
                        if (dist)
                        {
                            coord.moveRight(coord);
                            coord.moveBack(coord);
                        }
                        else
                        {
                            coord.moveRight(coord);
                            coord.moveBack(coord);
                            coord.moveRight(coord);
                            coord.moveBack(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 4:
                        south(coord, dist);
                        if (dist)
                        {
                            coord.moveBack(coord);
                        }
                        else
                        {
                            coord.moveBack(coord);
                            coord.moveBack(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 5:
                        // southW(coord, dist);
                        if (dist)
                        {
                            coord.moveBack(coord);
                            coord.moveLeft(coord);
                        }
                        else
                        {
                            coord.moveBack(coord);
                            coord.moveLeft(coord);
                            coord.moveBack(coord);
                            coord.moveLeft(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 6:
                        // west(coord, dist);
                        if (dist)
                        {
                            coord.moveLeft(coord);
                        }
                        else
                        {
                            coord.moveLeft(coord);
                            coord.moveLeft(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    case 7:
                        // northW(coord, dist);
                        if (dist)
                        {
                            coord.moveInFront(coord);
                            coord.moveLeft(coord);
                        }
                        else
                        {
                            coord.moveInFront(coord);
                            coord.moveLeft(coord);
                            coord.moveInFront(coord);
                            coord.moveLeft(coord);
                        }
                        state = State::POLE_FOUND;
                        break;
                    default:
                        state = State::NO_POLE;
                        break;
                    }
                }
            }
            break;
        case State::POLE_FOUND:
            DDRA |= (1 << PA5) | (1 << PA4);
            sound.highPitchSound();
            DDRA &= ~((1 << PA5) | (1 << PA4));
            sei();
            _delay_ms(1000);
            while (state == State::POLE_FOUND)
            {
                transmissionUART(coord.getPointX());
                mem.ecriture(adr++, coord.getPointX());
                _delay_ms(5);
                transmissionUART(coord.getPointY());
                mem.ecriture(adr++, coord.getPointY());
                _delay_ms(5);
                memWrited++;
                do
                {
                    for (int i = 0; i < 20; i++)
                    {
                        led.setAmber(); // Led flash ambre à 2Hz
                    }
                    led.setOff();
                  //  _delay_ms(250);
                } while (!interruptPressed);

                if (interruptPressed)
                {
                    state = State::FINDING_POLE;
                    interruptPressed = false;
                    led.setOff();
                }
            }
            break;
        case State::NO_POLE:
            led.setRed();
            DDRA |= (1 << PA5) | (1 << PA4);
            sound.playnote(sound.defineFrequence(48)); // Le son grave pendant 2s
            _delay_ms(2000);
            DDRA &= ~((1 << PA5) | (1 << PA4));
            while (state == State::NO_POLE)
            {
                led.setRedFlash(); // Led flash rouge à 2Hz
                // Le robot ne fait plus rien après (attends le reset)
            }
            break;
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
}