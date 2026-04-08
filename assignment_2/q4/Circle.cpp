#include "Circle.h"

#include <QPainter>

Circle::Circle(QObject *parent)
    : Circle(1, Qt::black, Qt::white, 1, parent)
{
}

Circle::Circle(int penWidth,
               const QColor &penColour,
               const QColor &fillColour,
               int radius,
               QObject *parent)
    : Shape1Property(penWidth, penColour, fillColour, radius, parent)
{
}

void Circle::draw(QPainter &painter, const QRect &bounds) const
{
    const int diameter = property1() * 2;
    const QRect shapeRect = centeredRect(bounds, diameter, diameter);

    applyPenAndBrush(painter);
    painter.drawEllipse(shapeRect);
}
