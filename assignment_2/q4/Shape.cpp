#include "Shape.h"

#include <QBrush>
#include <QPainter>
#include <QPen>
#include <QRect>

#include <algorithm>

Shape::Shape(int penWidth,
             const QColor &penColour,
             const QColor &fillColour,
             QObject *parent)
    : QObject(parent)
    , m_penColour(penColour)
    , m_fillColour(fillColour)
{
    setPenWidth(penWidth);
}

int Shape::penWidth() const
{
    return m_penWidth;
}

QColor Shape::penColour() const
{
    return m_penColour;
}

QColor Shape::fillColour() const
{
    return m_fillColour;
}

void Shape::setPenWidth(int penWidth)
{
    m_penWidth = std::max(1, penWidth);
}

void Shape::setPenColour(const QColor &penColour)
{
    m_penColour = penColour;
}

void Shape::setFillColour(const QColor &fillColour)
{
    m_fillColour = fillColour;
}

void Shape::applyPenAndBrush(QPainter &painter) const
{
    QPen pen(m_penColour);
    pen.setWidth(m_penWidth);
    painter.setPen(pen);
    painter.setBrush(QBrush(m_fillColour));
}

QRect Shape::centeredRect(const QRect &bounds, int requestedWidth, int requestedHeight)
{
    if (requestedWidth <= 0 || requestedHeight <= 0) {
        return QRect();
    }

    const double widthScale = static_cast<double>(bounds.width()) / requestedWidth;
    const double heightScale = static_cast<double>(bounds.height()) / requestedHeight;
    const double scale = std::min(1.0, std::min(widthScale, heightScale));

    const int width = std::max(1, static_cast<int>(requestedWidth * scale));
    const int height = std::max(1, static_cast<int>(requestedHeight * scale));
    const int x = bounds.center().x() - (width / 2);
    const int y = bounds.center().y() - (height / 2);

    return QRect(x, y, width, height);
}
