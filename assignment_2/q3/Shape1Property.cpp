#include "Shape1Property.h"

#include <algorithm>

Shape1Property::Shape1Property(int penWidth,
                               const QColor &penColour,
                               const QColor &fillColour,
                               int property1)
    : Shape(penWidth, penColour, fillColour)
{
    setProperty1(property1);
}

int Shape1Property::property1() const
{
    return m_property1;
}

void Shape1Property::setProperty1(int property1)
{
    m_property1 = std::max(1, property1);
}
