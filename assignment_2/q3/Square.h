#pragma once

#include "Shape1Property.h"

/**
 * Concrete shape that draws a square using the first property as side length.
 */
class Square : public Shape1Property
{
    Q_OBJECT
    Q_CLASSINFO("ShapeXmlType", "Square")

public:
    Q_INVOKABLE Square(QObject *parent = nullptr);
    Square(int penWidth,
           const QColor &penColour,
           const QColor &fillColour,
           int sideLength,
           QObject *parent = nullptr);

    void draw(QPainter &painter, const QRect &bounds) const override;
};
