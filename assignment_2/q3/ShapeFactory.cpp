#include "ShapeFactory.h"

#include "Circle.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Shape.h"
#include "Square.h"

#include <QString>

Shape *ShapeFactory::createShape(const QString &shapeType,
                                 int penWidth,
                                 const QColor &penColour,
                                 const QColor &fillColour,
                                 int property1,
                                 int property2) const
{
    if (shapeType == "Circle") {
        return new Circle(penWidth, penColour, fillColour, property1);
    }

    if (shapeType == "Square") {
        return new Square(penWidth, penColour, fillColour, property1);
    }

    if (shapeType == "Rectangle") {
        return new Rectangle(penWidth, penColour, fillColour, property1, property2);
    }

    return new Ellipse(penWidth, penColour, fillColour, property1, property2);
}
