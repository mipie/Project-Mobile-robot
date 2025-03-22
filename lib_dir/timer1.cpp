#include <avr/io.h>
#include <timer1.h>

Timer::Timer()
{
}

void Timer::startTimer(uint16_t time, uint8_t mode) // mode 0 = normal, mode 1 = CTC
{
   int realTime = time * 7812;
   TCNT1 = 0;
   OCR1A = realTime;
   TCCR1A |= (1 << COM1A0) | (1 << COM1A1);
   TCCR1B |= (1 << CS10) | (1 << CS12) | (mode << WGM12);
   TCCR1C = 0;
   TIMSK1 |= (1 << OCIE1A);
}
