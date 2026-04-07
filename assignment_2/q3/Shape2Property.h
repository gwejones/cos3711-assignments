#pragma once

#include "Shape1Property.h"

/**
 * Base class for shapes that use two configurable geometric properties.
 */
class Shape2Property : public Shape1Property
{
    Q_OBJECT
    Q_PROPERTY(int property2 READ property2 WRITE setProperty2)

public:
    explicit Shape2Property(int penWidth = 1,
                            const QColor &penColour = Qt::black,
                            const QColor &fillColour = Qt::white,
                            int property1 = 1,
                            int property2 = 1,
                            QObject *parent = nullptr);
    ~Shape2Property() override = default;

    int property2() const;
    void setProperty2(int property2);

    virtual void draw(QPainter &painter, const QRect &bounds) const override = 0;

private:
    int m_property2 = 1;
};
