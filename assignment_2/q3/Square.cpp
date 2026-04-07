#include "Square.h"

#include <QPainter>

Square::Square(int penWidth,
               const QColor &penColour,
               const QColor &fillColour,
               int sideLength)
    : Shape1Property(penWidth, penColour, fillColour, sideLength)
{
}

void Square::draw(QPainter &painter, const QRect &bounds) const
{
    const QRect shapeRect = centeredRect(bounds, property1(), property1());

    applyPenAndBrush(painter);
    painter.drawRect(shapeRect);
}
