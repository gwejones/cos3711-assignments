#pragma once

#include "Shape1Property.h"

class Circle : public Shape1Property
{
public:
    Circle(int penWidth,
           const QColor &penColour,
           const QColor &fillColour,
           int radius);

    void draw(QPainter &painter, const QRect &bounds) const override;
};
