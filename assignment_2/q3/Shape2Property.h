#pragma once

#include "Shape1Property.h"

/**
 * Base class for shapes that use two configurable geometric properties.
 */
class Shape2Property : public Shape1Property
{
public:
    Shape2Property(int penWidth,
                   const QColor &penColour,
                   const QColor &fillColour,
                   int property1,
                   int property2);
    ~Shape2Property() override = default;

    int property2() const;
    void setProperty2(int property2);

    virtual void draw(QPainter &painter, const QRect &bounds) const override = 0;

private:
    int m_property2 = 1;
};
