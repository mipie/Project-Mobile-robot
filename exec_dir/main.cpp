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

Navigation nav;
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
    _delay_ms(200);
    nav.turnOff();
    _delay_ms(1000);
}

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

int main()
{

    Navigation nav;
    can mycan;
    Led led(&DDRC, &PORTC, PC0, PC1);
    initialisationUART();
    bool detected = false;
    int compteur = 0;
    bool vu = false;

    while (true)
    {
        nav.moveForward(50);
    }

    uint8_t val;

    while (!detected)
    {

        val = (mycan.lecture(PA0) >> 2); // On enleve les 2 bits les moins significatifs

        if (val > 25)
        {
            detected = true;
            break;
        }

        turnRight45();
        nav.turnOff();

        val = (mycan.lecture(PA0) >> 2);

        if (val > 25)
        {
            detected = true;
            break;
        }

        unPeuG();
        nav.turnOff();

        val = (mycan.lecture(PA0) >> 2);

        if (val > 25)
        {
            detected = true;
            break;
        }

        unPeuD();
        nav.turnOff();

        val = (mycan.lecture(PA0) >> 2);

        if (val > 25)
        {
            detected = true;
            break;
        }
    }

    while (detected)
    {


        val = (mycan.lecture(PA0) >> 2);


        if (vu && val<25)
        {
            nav.turnOff();
            unPeuG();
            val = (mycan.lecture(PA0) >> 2);
            if(val>24){
                vu=false;
            }
            unPeuD();
            val = (mycan.lecture(PA0) >> 2);
            if(val>24){
                vu=false;
            }
        }

        if (val >= 25 && val < 30)
        {

            led.setGreen();
            nav.moveForward(50);
            vu = true;

            val = (mycan.lecture(PA0) >> 2);
        }

        val = (mycan.lecture(PA0) >> 2);

        if (val >= 30 && val < 90)
        {

            led.setRed();
            nav.moveForward(50);
            vu = true;

            val = (mycan.lecture(PA0) >> 2);
        }

        val = (mycan.lecture(PA0) >> 2);
        if (val >= 90)
        {

            transmissionUART(val);
            while (true)
            {

                nav.turnOff();

                led.setOff();
            }

            val = (mycan.lecture(PA0) >> 2);
        }
    }

    return 0;
}*/