#include "Rectangle.h"

#include <QPainter>

Rectangle::Rectangle(QObject *parent)
    : Rectangle(1, Qt::black, Qt::white, 1, 1, parent)
{
}

Rectangle::Rectangle(int penWidth,
                     const QColor &penColour,
                     const QColor &fillColour,
                     int width,
                     int height,
                     QObject *parent)
    : Shape2Property(penWidth, penColour, fillColour, width, height, parent)
{
}

void Rectangle::draw(QPainter &painter, const QRect &bounds) const
{
    const QRect shapeRect = centeredRect(bounds, property1(), property2());

    applyPenAndBrush(painter);
    painter.drawRect(shapeRect);
}
