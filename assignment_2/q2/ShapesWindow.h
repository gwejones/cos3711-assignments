#pragma once

#include "ShapeFactory.h"

#include <QWidget>

class QColor;
class QComboBox;
class QLabel;
class QSpinBox;
class QString;

class DrawingCanvas;

/**
 * Main window that gathers user input and coordinates shape creation.
 */
class ShapesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ShapesWindow(QWidget *parent = nullptr);

private slots:
    void onShapeSelectionChanged(int index);
    void onCreateShapeClicked();

private:
    static QColor toColour(const QString &name);

    void updatePropertyState();
    void createShapeFromInput();

    QComboBox *m_shapeComboBox = nullptr;
    QSpinBox *m_property1SpinBox = nullptr;
    QLabel *m_property2Label = nullptr;
    QSpinBox *m_property2SpinBox = nullptr;
    QSpinBox *m_penWidthSpinBox = nullptr;
    QComboBox *m_penColourComboBox = nullptr;
    QComboBox *m_fillColourComboBox = nullptr;
    DrawingCanvas *m_canvas = nullptr;
    ShapeFactory m_shapeFactory;
};
