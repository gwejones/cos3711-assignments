#pragma once

#include <QWidget>

class QPaintEvent;
class Shape;

/**
 * Widget responsibile for rendering the currently selected shape preview.
 */
class DrawingCanvas : public QWidget
{
public:
    explicit DrawingCanvas(QWidget *parent = nullptr);
    ~DrawingCanvas() override;

    void setShape(Shape *shape);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Shape *m_shape = nullptr;
};
