#include "Ellipse.h"

#include <QPainter>

Ellipse::Ellipse(QObject *parent)
    : Ellipse(1, Qt::black, Qt::white, 1, 1, parent)
{
}

Ellipse::Ellipse(int penWidth,
                 const QColor &penColour,
                 const QColor &fillColour,
                 int width,
                 int height,
                 QObject *parent)
    : Shape2Property(penWidth, penColour, fillColour, width, height, parent)
{
}

void Ellipse::draw(QPainter &painter, const QRect &bounds) const
{
    const QRect shapeRect = centeredRect(bounds, property1(), property2());

    applyPenAndBrush(painter);
    painter.drawEllipse(shapeRect);
}
