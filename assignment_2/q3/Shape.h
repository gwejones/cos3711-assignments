#pragma once

#include <QColor>

class QPainter;
class QRect;

/**
 * Defines the common interface and shared styling data for drawable shapes in the applicaiton.
 */
class Shape
{
public:
    Shape(int penWidth = 1,
          const QColor &penColour = Qt::black,
          const QColor &fillColour = Qt::white);
    virtual ~Shape() = default;

    virtual void draw(QPainter &painter, const QRect &bounds) const = 0;

    int penWidth() const;
    QColor penColour() const;
    QColor fillColour() const;

    void setPenWidth(int penWidth);
    void setPenColour(const QColor &penColour);
    void setFillColour(const QColor &fillColour);

protected:
    void applyPenAndBrush(QPainter &painter) const;
    static QRect centeredRect(const QRect &bounds, int requestedWidth, int requestedHeight);

private:
    int m_penWidth = 1;
    QColor m_penColour = Qt::black;
    QColor m_fillColour = Qt::white;
};
