#pragma once

#include <QColor>
#include <QString>

class Shape;

class ShapeFactory
{
public:
    Shape *createShape(const QString &shapeType,
                       int penWidth,
                       const QColor &penColour,
                       const QColor &fillColour,
                       int property1,
                       int property2) const;
};
