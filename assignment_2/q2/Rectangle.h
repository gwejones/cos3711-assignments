#pragma once

#include "Shape2Property.h"

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
