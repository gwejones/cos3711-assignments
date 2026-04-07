#include "Rectangle.h"

#include <QPainter>

Rectangle::Rectangle(int penWidth,
                     const QColor &penColour,
                     const QColor &fillColour,
                     int width,
                     int height)
    : Shape2Property(penWidth, penColour, fillColour, width, height)
{
}

void Rectangle::draw(QPainter &painter, const QRect &bounds) const
{
    const QRect shapeRect = centeredRect(bounds, property1(), property2());

    applyPenAndBrush(painter);
    painter.drawRect(shapeRect);
}
