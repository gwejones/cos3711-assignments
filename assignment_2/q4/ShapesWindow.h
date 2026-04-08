#pragma once

#include "ShapeFactory.h"
#include "ShapeXmlSerializer.h"

#include <QWidget>

class QColor;
class QComboBox;
class QLabel;
class QPushButton;
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
    void onPreviousClicked();
    void onNextClicked();

private:
    static QColor toColour(const QString &name);
    static QString resolveShapesXmlPath();

    void updatePropertyState();
    void updateNavigationState();
    void displayCurrentShape();
    void createShapeFromInput();
    void loadShapesFromXml();

    QComboBox *m_shapeComboBox = nullptr;
    QSpinBox *m_property1SpinBox = nullptr;
    QLabel *m_property2Label = nullptr;
    QSpinBox *m_property2SpinBox = nullptr;
    QSpinBox *m_penWidthSpinBox = nullptr;
    QComboBox *m_penColourComboBox = nullptr;
    QComboBox *m_fillColourComboBox = nullptr;
    QPushButton *m_previousButton = nullptr;
    QPushButton *m_nextButton = nullptr;
    DrawingCanvas *m_canvas = nullptr;
    ShapeFactory m_shapeFactory;
    ShapeXmlSerializer m_shapeXmlSerializer;
};
