#include "point.h"
#include "timer1.h"
#include "navigation.h"
#include "wheel.h"

Point::Point(uint8_t x , uint8_t y) : x_(x), y_(y)

{


}

uint8_t Point::getPointX() const
{
    return x_;
}

uint8_t Point::getPointY() const
{
    return y_;
}

void Point::moveInFront(Point &point) const
{
    point.y_ += 1;
}

void Point::moveBack(Point &point) const
{
    point.y_ -= 1;
}

void Point::moveRight(Point &point) const
{   
    point.x_ += 1; 
}

void Point::moveLeft(Point &point) const
{
    point.x_ -= 1;
}

void Point::setPoint(uint8_t x, uint8_t y) 
{
    x_ = x;
    y_ = y;
}
