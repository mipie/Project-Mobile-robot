#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <memoire_24.h>
#include "../lib_dir/communication.h"
#include "led.h"
#include "debug.h"

int main()
{

    uint16_t address = 0;
    uint16_t size;
    uint8_t data;
    Communication uart;
    Memoire24CXXX memory ;
    Led led(&DDRA, &PORTA, PA0, PA1);

   
    data = uart.readUART();
    memory .ecriture(address++, data);
    _delay_ms(5);

    size = data << 8;

    data = uart.readUART();
    memory .ecriture(address++, data);
    _delay_ms(5);

    size += data;
    while (address < size)
    {
        led.setGreen();
        data = uart.readUART();
        memory .ecriture(address++, data);
        _delay_ms(5);
    }
    
    led.setGreen();
    _delay_ms(2000);
    led.setOff();
}