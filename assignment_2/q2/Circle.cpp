#include "Circle.h"

#include <QPainter>

Circle::Circle(int penWidth,
               const QColor &penColour,
               const QColor &fillColour,
               int radius)
    : Shape1Property(penWidth, penColour, fillColour, radius)
{
}

void Circle::draw(QPainter &painter, const QRect &bounds) const
{
    const int diameter = property1() * 2;
    const QRect shapeRect = centeredRect(bounds, diameter, diameter);

    applyPenAndBrush(painter);
    painter.drawEllipse(shapeRect);
}
