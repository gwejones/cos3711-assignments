#pragma once

#include "Shape2Property.h"

/**
 * Concrete shape that draws a rectangle from width and height values.
 */
class Rectangle : public Shape2Property
{
    Q_OBJECT
    Q_CLASSINFO("ShapeXmlType", "Rectangle")

public:
    Q_INVOKABLE Rectangle(QObject *parent = nullptr);
    Rectangle(int penWidth,
              const QColor &penColour,
              const QColor &fillColour,
              int width,
              int height,
              QObject *parent = nullptr);

    void draw(QPainter &painter, const QRect &bounds) const override;
};
