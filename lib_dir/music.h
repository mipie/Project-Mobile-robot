#pragma once
#ifndef F_CPU
#define F_CPU 8000000
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

class Music
{
    public:
        Music();
        void playnote(double frequence);
        void makePause();
        double defineFrequence(int note);
        void highPitchSound();
        void playRickRolled();
    private:
    //...//
};