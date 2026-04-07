#pragma once

#include "Shape2Property.h"

/**
 * Concrete shape that draws a rectangle from width and height values.
 */
class Rectangle : public Shape2Property
{
public:
    Rectangle(int penWidth,
              const QColor &penColour,
              const QColor &fillColour,
              int width,
              int height);

    void draw(QPainter &painter, const QRect &bounds) const override;
};
