#pragma once

#include "Shape1Property.h"

/**
 * Concrete shape that draws a square using the first property as side length.
 */
class Square : public Shape1Property
{
public:
    Square(int penWidth,
           const QColor &penColour,
           const QColor &fillColour,
           int sideLength);

    void draw(QPainter &painter, const QRect &bounds) const override;
};
