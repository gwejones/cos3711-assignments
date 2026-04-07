#pragma once

#include "Shape2Property.h"

class Ellipse : public Shape2Property
{
public:
    Ellipse(int penWidth,
            const QColor &penColour,
            const QColor &fillColour,
            int width,
            int height);

    void draw(QPainter &painter, const QRect &bounds) const override;
};
