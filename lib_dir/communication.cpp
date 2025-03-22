#include "communication.h"
#include <stdio.h>

Communication::Communication()
{
    initialisationUART();
}

void Communication::initialisationUART()
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

uint8_t Communication::readUART()
{

    do
    {
    } while (!(UCSR0A & (1 << RXC0)));

    return (UDR0);
}

void Communication::transmissionUART(uint8_t data)
{

    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = data;
}

void Communication::sendMessage(const char *word)
{
    int i = 0;
    while (word[i] != '\0')
    {
        transmissionUART(word[i++]);
    }
}
/*
void sendPosition(const char message[], uint8_t value)
{
    char buffer[50];
    uint8_t *data;
    memoire.lecture(adress, data);
    uint8_t messageLength = sprintf(buffer, message, value);

    for (uint8_t i = 0; i < value; i++)
    {
        if (buffer[i] == *data)

            for (uint8_t i = 0; i < messageLength; i++)
            {
                comm.transmissionUART(buffer[i]);
            }
    }

}*/

