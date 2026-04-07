#include "Square.h"

#include <QPainter>

Square::Square(QObject *parent)
    : Square(1, Qt::black, Qt::white, 1, parent)
{
}

Square::Square(int penWidth,
               const QColor &penColour,
               const QColor &fillColour,
               int sideLength,
               QObject *parent)
    : Shape1Property(penWidth, penColour, fillColour, sideLength, parent)
{
}

void Square::draw(QPainter &painter, const QRect &bounds) const
{
    const QRect shapeRect = centeredRect(bounds, property1(), property1());

    applyPenAndBrush(painter);
    painter.drawRect(shapeRect);
}
