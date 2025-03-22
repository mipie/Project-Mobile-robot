#include <music.h>
#include <math.h>

Music::Music()
{
   
}

double Music::defineFrequence(int note)
{
   double frequence = 0;
   if (note == 45)
   {
      frequence = 141.045;
   }
   if (note == 46)
   {
      frequence = 133.073;
   }
   if (note == 47)
   {
      frequence = 125.548;
   }
   if (note == 48)
   {
      frequence = 118.446;
   }
   if (note == 49)
   {
      frequence = 111.742;
   }
   if (note == 50)
   {
      frequence = 105.414;
   }
   if (note == 51)
   {
      frequence = 99.441;
   }
   if (note == 52)
   {
      frequence = 93.804;
   }
   if (note == 53)
   {
      frequence = 88.483;
   }
   if (note == 54)
   {
      frequence = 83.461;
   }
   if (note == 55)
   {
      frequence = 78.720;
   }
   if (note == 56)
   {
      frequence = 74.246;
   }
   if (note == 57)
   {
      frequence = 70.023;
   }
   if (note == 58)
   {
      frequence = 66.037;
   }
   if (note == 59)
   {
      frequence = 62.274;
   }
   if (note == 60)
   {
      frequence = 58.723;
   }
   if (note == 61)
   {
      frequence = 55.371;
   }
   if (note == 62)
   {
      frequence = 52.207;
   }
   if (note == 63)
   {
      frequence = 49.221;
   }
   if (note == 64)
   {
      frequence = 46.402;
   }
   if (note == 65)
   {
      frequence = 43.742;
   }
   if (note == 66)
   {
      frequence = 41.230;
   }
   if (note == 67)
   {
      frequence = 38.860;
   }
   if (note == 68)
   {
      frequence = 36.623;
   }
   if (note == 69)
   {
      frequence = 34.511;
   }
   if (note == 70)
   {
      frequence = 32.518;
   }
   if (note == 71)
   {
      frequence = 30.637;
   }
   if (note == 72)
   {
      frequence = 28.861;
   }
   if (note == 73)
   {
      frequence = 27.185;
   }
   if (note == 74)
   {
      frequence = 25.603;
   }
   if (note == 75)
   {
      frequence = 24.110;
   }
   if (note == 76)
   {
      frequence = 22.701;
   }
   if (note == 77)
   {
      frequence = 21.371;
   }
   if (note == 78)
   {
      frequence = 20.115;
   }
   if (note == 79)
   {
      frequence = 18.930;
   }
   if (note == 80)
   {
      frequence = 17.811;
   }
   if (note == 81)
   {
      frequence = 16.756;
   }
   return frequence;
}

void Music::playnote(double frequence)
{
   TCNT2 = 0;
   OCR2A = frequence;
   TCCR2A = (1 << COM2A0) | (0 << COM2B0) | (1 << WGM21); // Toggle on compare match, mode CTC
   TCCR2B = (1 << CS21) | (1 << CS22); // Prescaler 256
   TIMSK2 = (1 << OCIE2A) | (0 << OCIE2B); // Interrupt enable
}

void Music::makePause()
{
   OCR2A = 0;
   TCCR2A = 0;
   TCCR2B = 0;
}

void Music::highPitchSound()
{
   sei();
   playnote(defineFrequence(74));
   _delay_ms(300);
   cli();
   sei();
   _delay_ms(300);
   playnote(defineFrequence(72));
   _delay_ms(300);
   cli();
   sei();
   _delay_ms(300);
   playnote(defineFrequence(77));
   _delay_ms(500);
   cli();
   _delay_ms(300);
}

void Music::playRickRolled()
{
   sei();
    playnote(defineFrequence(50));
    _delay_ms(125); 
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(52));
    _delay_ms(125);
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(55));
    _delay_ms(125);
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(52));
    _delay_ms(125);
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(59));
    _delay_ms(375);
    cli();
    _delay_ms(20);
    sei();
    playnote(defineFrequence(59));
    _delay_ms(375);
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(57));
    _delay_ms(500);
    cli();
    _delay_ms(30);
    sei();
    playnote(defineFrequence(50));
    _delay_ms(125); 
    cli();
    _delay_ms(15);
    sei();
    playnote(defineFrequence(52));
    _delay_ms(125);
    cli();
    _delay_ms(15);
    sei();
    playnote(defineFrequence(55));
    _delay_ms(125);
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(52));
    _delay_ms(125);
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(57));
    _delay_ms(375);
    cli();
    _delay_ms(20);
    sei();
    playnote(defineFrequence(57));
    _delay_ms(375);
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(55));
    _delay_ms(375);
    cli();
    _delay_ms(5);
    sei();
    playnote(defineFrequence(54));
    _delay_ms(125);
    cli();
    _delay_ms(5);
    sei();
    playnote(defineFrequence(52));
    _delay_ms(250);
    cli();
    _delay_ms(20);
    sei();
    playnote(defineFrequence(50));
    _delay_ms(125); 
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(52));
    _delay_ms(125);
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(55));
    _delay_ms(125);
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(52));
    _delay_ms(125);
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(55));
    _delay_ms(375);
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(57));
    _delay_ms(250);
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(54));
    _delay_ms(375);
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(52));
    _delay_ms(125);
    cli();
    _delay_ms(15);
    sei();
    playnote(defineFrequence(50));
    _delay_ms(250);
    cli();
    _delay_ms(30);
    sei();
    playnote(defineFrequence(50));
    _delay_ms(500);
    cli();
    sei();
    playnote(defineFrequence(50));
    _delay_ms(500);
    cli();
    _delay_ms(20);
    sei();
    playnote(defineFrequence(57));
    _delay_ms(750);
    cli();
    _delay_ms(10);
    sei();
    playnote(defineFrequence(55));
    _delay_ms(1250);
    cli();
}