#include "DrawingCanvas.h"

#include "Shape.h"

#include <QPainter>
#include <QPen>

namespace
{
constexpr int kCanvasMinimumHeight = 190;
constexpr int kCanvasBackgroundGray = 235;
constexpr int kCanvasBorderGray = 170;
constexpr int kCanvasInnerPadding = 16;
}

DrawingCanvas::DrawingCanvas(QWidget *parent)
    : QWidget(parent)
{
    setMinimumHeight(kCanvasMinimumHeight);
}

void DrawingCanvas::setShape(Shape *shape)
{
    if (m_shape == shape) {
        return;
    }

    m_shape = shape;
    update();
}

void DrawingCanvas::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    painter.fillRect(rect(), QColor(kCanvasBackgroundGray, kCanvasBackgroundGray, kCanvasBackgroundGray));

    QPen borderPen(QColor(kCanvasBorderGray, kCanvasBorderGray, kCanvasBorderGray));
    painter.setPen(borderPen);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    if (m_shape) {
        const QRect drawBounds = rect().adjusted(kCanvasInnerPadding,
                                                 kCanvasInnerPadding,
                                                 -kCanvasInnerPadding,
                                                 -kCanvasInnerPadding);
        m_shape->draw(painter, drawBounds);
    }
}
