#pragma once

#include "Shape2Property.h"

/**
 * Concrete shape that draws an ellipse from width and height values.
 */
class Ellipse : public Shape2Property
{
    Q_OBJECT

public:
    Q_INVOKABLE Ellipse(QObject *parent = nullptr);
    Ellipse(int penWidth,
            const QColor &penColour,
            const QColor &fillColour,
            int width,
            int height,
            QObject *parent = nullptr);

    void draw(QPainter &painter, const QRect &bounds) const override;
};
