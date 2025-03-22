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
#include "point.h"

Navigation nav;
Point coord(0, 0);
void turnLeft45()
{
    nav.turnRight();
    _delay_ms(420);
    nav.turnOff();
    _delay_ms(1000);
}

void turnRight45()
{
    nav.turnLeft();
    _delay_ms(420);
    nav.turnOff();
    _delay_ms(1000);
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

void moveIfHere(bool detected, uint8_t val)
{
    while (detected)
    {
        nav.moveForward(50);
        if (val > 100)
        {
            detected = false;
        }
    }
    nav.turnOff();
}

int main()
{
    bool detected = false;
    bool dist = false;
    can cann;
    uint8_t counter = 0, val = 0;
    val = (cann.lecture(PA0) >> 2);

    if (coord.getPointX() == 0 && coord.getPointY() == 0 && isFacingTop)
    {
        counter = 0;
        while (!detected)
        {
            if (val < 30)
            {
                detected = true;
            }
            turnLeft45();
            counter++;
            moveIfHere(detected, val);
            detected = false;
            if (val < 40)
            {
                dist = true;
            }
            switch (counter)
            {
            case 0:
                north(coord, dist);
                break;
            case 1:
                northW(coord, dist);
                break;
            case 2:
                west(coord, dist);
                break;
            default:
                break;
            }
        }
    }
        if (coord.getPointX() == 0 && coord.getPointY() == 0 %% !isFacingTop)
        {
            counter = 0;
            while (!detected)
            {
                if (val < 30)
                {
                    detected = true;
                }
                turnLeft45();
                counter++;
                moveIfHere(detected, val);
                detected = false;
                if (val < 40)
                {
                    dist = true;
                }
                switch (counter)
                {
                case 0:
                    west(coord, dist);
                    break;
                case 1:
                    northW(coord, dist);
                    break;
                case 2:
                    north(coord, dist);
                    break;
                default:
                    break;
                }
            }
        }
            else if (coord.getPointX() == 7 && coord.getPointY() == 0)
            {
                counter = 0;
                while (!detected)
                {
                    if (val < 30)
                    {
                        detected = true;
                    }
                    turnLeft45();
                    counter++;
                }
                moveIfHere(detected, val);
                detected = false;
                if (val < 40)
                {
                    dist = true;
                }
                switch (counter)
                {
                case 0:
                    north(coord, dist);
                    break;
                case 1:
                    northW(coord, dist);
                    break;
                case 2:
                    west(coord, dist);
                    break;
                case 3:
                    southW(coord, dist);
                    break;
                case 4:
                    south(coord, dist);
                    break;
                case 5:
                    southE(coord, dist);
                    break;
                case 6:
                    east(coord, dist);
                    break;
                case 7:
                    northE(coord, dist);
                    break;
                default:
                    break;
                }
            }
            else if (coord.getPointX() == 7 && coord.getPointY() == 1)
            {
                counter = 0;
                while (!detected)
                {
                    if (val < 30)
                    {
                        detected = true;
                    }
                    turnLeft45();
                    counter++;
                }
                moveIfHere(detected, val);
                detected = false;
                if (val < 40)
                {
                    dist = true;
                }
                switch (counter)
                {
                case 0:
                    north(coord, dist);
                    break;
                case 1:
                    northW(coord, dist);
                    break;
                case 2:
                    west(coord, dist);
                    break;
                case 3:
                    southW(coord, dist);
                    break;
                case 4:
                    south(coord, dist);
                    break;
                case 5:
                    southE(coord, dist);
                    break;
                case 6:
                    east(coord, dist);
                    break;
                case 7:
                    northE(coord, dist);
                    break;
                default:
                    break;
                }
            }
            else if (coord.getPointX() == 7 && coord.getPointY() == 2)
            {
                counter = 0;
                while (!detected)
                {
                    if (val < 30)
                    {
                        detected = true;
                    }
                    turnLeft45();
                    counter++;
                }
                moveIfHere(detected, val);
                detected = false;
                if (val < 40)
                {
                    dist = true;
                }
                switch (counter)
                {
                case 0:
                    north(coord, dist);
                    break;
                case 1:
                    northW(coord, dist);
                    break;
                case 2:
                    west(coord, dist);
                    break;
                case 3:
                    southW(coord, dist);
                    break;
                case 4:
                    south(coord, dist);
                    break;
                case 5:
                    southE(coord, dist);
                    break;
                case 6:
                    east(coord, dist);
                    break;
                case 7:
                    northE(coord, dist);
                    break;
                default:
                    break;
                }
            }
            else if (coord.getPointX() == 7 && coord.getPointY() == 3)
            {
                counter = 0;
                while (!detected)
                {
                    if (val < 30)
                    {
                        detected = true;
                    }
                    turnLeft45();
                    counter++;
                }
                moveIfHere(detected, val);
                detected = false;
                if (val < 40)
                {
                    dist = true;
                }
                switch (counter)
                {
                case 0:
                    north(coord, dist);
                    break;
                case 1:
                    northW(coord, dist);
                    break;
                case 2:
                    west(coord, dist);
                    break;
                case 3:
                    southW(coord, dist);
                    break;
                case 4:
                    south(coord, dist);
                    break;
                case 5:
                    southE(coord, dist);
                    break;
                case 6:
                    east(coord, dist);
                    break;
                case 7:
                    northE(coord, dist);
                    break;
                default:
                    break;
                }
            }
            else
            {
                counter = 0;
                while (!detected)
                {
                    if (val < 30)
                    {
                        detected = true;
                    }
                    turnRight45();
                    counter++;
                }
                moveIfHere(detected, val);
                detected = false;
                if (val < 40)
                {
                    dist = true;
                }
                switch (counter)
                {
                case 0:
                    north(coord, dist);
                    break;
                case 1:
                    northE(coord, dist);
                    break;
                case 2:
                    east(coord, dist);
                    break;
                case 3:
                    southE(coord, dist);
                    break;
                case 4:
                    south(coord, dist);
                    break;
                case 5:
                    southW(coord, dist);
                    break;
                case 6:
                    west(coord, dist);
                    break;
                case 7:
                    northW(coord, dist);
                    break;
                default:
                    break;
                }
            }
        }*/