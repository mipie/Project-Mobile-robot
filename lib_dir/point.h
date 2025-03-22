#pragma once
#ifndef POINT_H
#define POINT_H
#define F_CPU 8000000UL
#include <util/delay.h>
#include <stdint.h>
#include <avr/io.h>

class Point
{
public:
    Point(uint8_t x, uint8_t y);
    uint8_t getPointX() const;
    uint8_t getPointY() const;
    //void changeCoordination(uint8_t x, uint8_t y);
    void moveRight( Point &point) const;
    void moveLeft(Point &point) const;
    void moveInFront(Point &point) const;
    void moveBack(Point &point) const;
    void setPoint(uint8_t x, uint8_t y);
   // ~Point();
private:
    uint8_t x_;
    uint8_t y_;
};
#endif


