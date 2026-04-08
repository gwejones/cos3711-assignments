#pragma once

#include "Shape1Property.h"

/**
 * Concrete shape that draws a circle using the first propety as radius.
 */
class Circle : public Shape1Property
{
    Q_OBJECT
    Q_CLASSINFO("ShapeXmlType", "Circle")

public:
    Q_INVOKABLE Circle(QObject *parent = nullptr);
    Circle(int penWidth,
           const QColor &penColour,
           const QColor &fillColour,
           int radius,
           QObject *parent = nullptr);

    void draw(QPainter &painter, const QRect &bounds) const override;
};
