#pragma once

#include "Shape.h"

/**
 * Base class for shapes that use one configurable geometry property.
 */
class Shape1Property : public Shape
{
    Q_OBJECT
    Q_PROPERTY(int property1 READ property1 WRITE setProperty1)

public:
    explicit Shape1Property(int penWidth = 1,
                            const QColor &penColour = Qt::black,
                            const QColor &fillColour = Qt::white,
                            int property1 = 1,
                            QObject *parent = nullptr);
    ~Shape1Property() override = default;

    int property1() const;
    void setProperty1(int property1);

    virtual void draw(QPainter &painter, const QRect &bounds) const override = 0;

private:
    int m_property1 = 1;
};
