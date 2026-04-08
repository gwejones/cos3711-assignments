#include "Shape2Property.h"

#include <algorithm>

Shape2Property::Shape2Property(int penWidth,
                               const QColor &penColour,
                               const QColor &fillColour,
                               int property1,
                               int property2,
                               QObject *parent)
    : Shape1Property(penWidth, penColour, fillColour, property1, parent)
{
    setProperty2(property2);
}

int Shape2Property::property2() const
{
    return m_property2;
}

void Shape2Property::setProperty2(int property2)
{
    m_property2 = std::max(1, property2);
}
