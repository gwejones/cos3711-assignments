#pragma once

#include "Shape.h"

class Shape1Property : public Shape
{
public:
    Shape1Property(int penWidth,
                   const QColor &penColour,
                   const QColor &fillColour,
                   int property1);
    ~Shape1Property() override = default;

    int property1() const;
    void setProperty1(int property1);

    virtual void draw(QPainter &painter, const QRect &bounds) const override = 0;

private:
    int m_property1 = 1;
};
