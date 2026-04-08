#include "ShapesWindow.h"

#include "DrawingCanvas.h"
#include "Shape.h"
#include "ShapeList.h"

#include <QCoreApplication>
#include <QColor>
#include <QComboBox>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QString>
#include <QStringList>
#include <QVBoxLayout>

namespace
{
constexpr int kMinPropertyValue = 1;
constexpr int kMaxPropertyValue = 500;
constexpr int kDefaultProperty1 = 100;
constexpr int kDefaultProperty2 = 50;
constexpr int kMinPenWidth = 1;
constexpr int kMaxPenWidth = 20;
constexpr int kDefaultPenWidth = 3;
constexpr int kWindowWidth = 300;
constexpr int kWindowHeight = 460;
}

ShapesWindow::ShapesWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Shapes - Question 4");

    QLabel *shapeLabel = new QLabel("Shape");
    QLabel *property1Label = new QLabel("Property 1");
    m_property2Label = new QLabel("Property 2");
    QLabel *penWidthLabel = new QLabel("Pen width");
    QLabel *penColourLabel = new QLabel("Pen colour");
    QLabel *fillColourLabel = new QLabel("Fill colour");

    m_shapeComboBox = new QComboBox();
    m_shapeComboBox->addItems({"Ellipse", "Rectangle", "Circle", "Square"});

    m_property1SpinBox = new QSpinBox();
    m_property1SpinBox->setRange(kMinPropertyValue, kMaxPropertyValue);
    m_property1SpinBox->setValue(kDefaultProperty1);

    m_property2SpinBox = new QSpinBox();
    m_property2SpinBox->setRange(kMinPropertyValue, kMaxPropertyValue);
    m_property2SpinBox->setValue(kDefaultProperty2);

    m_penWidthSpinBox = new QSpinBox();
    m_penWidthSpinBox->setRange(kMinPenWidth, kMaxPenWidth);
    m_penWidthSpinBox->setValue(kDefaultPenWidth);

    m_penColourComboBox = new QComboBox();
    m_penColourComboBox->addItems({"Black", "Blue", "Green", "Red"});
    m_penColourComboBox->setCurrentText("Black");

    m_fillColourComboBox = new QComboBox();
    m_fillColourComboBox->addItems({"Black", "Blue", "Green", "Red"});
    m_fillColourComboBox->setCurrentText("Green");

    QPushButton *createShapeButton = new QPushButton("Create shape");
    m_backupButton = new QPushButton("Backup");
    m_restoreButton = new QPushButton("Restore");
    m_restoreButton->setEnabled(false);
    m_previousButton = new QPushButton("Previous");
    m_nextButton = new QPushButton("Next");

    m_canvas = new DrawingCanvas();

    QGridLayout *controlsLayout = new QGridLayout();
    controlsLayout->addWidget(shapeLabel, 0, 0);
    controlsLayout->addWidget(m_shapeComboBox, 0, 1);
    controlsLayout->addWidget(property1Label, 0, 2);
    controlsLayout->addWidget(m_property1SpinBox, 0, 3);
    controlsLayout->addWidget(penWidthLabel, 1, 0);
    controlsLayout->addWidget(m_penWidthSpinBox, 1, 1);
    controlsLayout->addWidget(m_property2Label, 1, 2);
    controlsLayout->addWidget(m_property2SpinBox, 1, 3);
    controlsLayout->addWidget(penColourLabel, 2, 0);
    controlsLayout->addWidget(m_penColourComboBox, 2, 1);
    controlsLayout->addWidget(fillColourLabel, 2, 2);
    controlsLayout->addWidget(m_fillColourComboBox, 2, 3);

    QHBoxLayout *actionsLayout = new QHBoxLayout();
    actionsLayout->addWidget(createShapeButton, 1);
    actionsLayout->addWidget(m_backupButton, 1);
    actionsLayout->addWidget(m_restoreButton, 1);

    QHBoxLayout *navigationLayout = new QHBoxLayout();
    navigationLayout->addWidget(m_previousButton);
    navigationLayout->addStretch();
    navigationLayout->addWidget(m_nextButton);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(controlsLayout);
    mainLayout->addLayout(actionsLayout);
    mainLayout->addWidget(m_canvas);
    mainLayout->addLayout(navigationLayout);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(10);

    connect(m_shapeComboBox,
            qOverload<int>(&QComboBox::currentIndexChanged),
            this,
            &ShapesWindow::onShapeSelectionChanged);
    connect(createShapeButton,
            &QPushButton::clicked,
            this,
            &ShapesWindow::onCreateShapeClicked);
    connect(m_backupButton,
            &QPushButton::clicked,
            this,
            &ShapesWindow::onBackupClicked);
    connect(m_restoreButton,
            &QPushButton::clicked,
            this,
            &ShapesWindow::onRestoreClicked);
    connect(m_previousButton,
            &QPushButton::clicked,
            this,
            &ShapesWindow::onPreviousClicked);
    connect(m_nextButton,
            &QPushButton::clicked,
            this,
            &ShapesWindow::onNextClicked);

    updatePropertyState();
    loadShapesFromXml();
    updateNavigationState();
    resize(kWindowWidth, kWindowHeight);
}

ShapesWindow::~ShapesWindow()
{
    delete m_backupMemento;
}

QColor ShapesWindow::toColour(const QString &name)
{
    const QColor colour(name.toLower());
    return colour.isValid() ? colour : QColor(Qt::black);
}

QString ShapesWindow::resolveShapesXmlPath()
{
    const QString applicationDirPath = QCoreApplication::applicationDirPath();
    const QStringList candidatePaths = {
        QDir::current().filePath("shapes.xml"),
        QDir::current().filePath("data/shapes.xml"),
        QDir(applicationDirPath).filePath("data/shapes.xml"),
        QDir(applicationDirPath).filePath("../data/shapes.xml")
    };

    for (const QString &candidatePath : candidatePaths) {
        const QFileInfo fileInfo(candidatePath);
        if (fileInfo.exists() && fileInfo.isFile()) {
            return fileInfo.absoluteFilePath();
        }
    }

    return QDir(applicationDirPath).filePath("../data/shapes.xml");
}

void ShapesWindow::onShapeSelectionChanged(int index)
{
    updatePropertyState();
}

void ShapesWindow::onCreateShapeClicked()
{
    createShapeFromInput();
    updateNavigationState();
}

void ShapesWindow::onBackupClicked()
{
    ShapeList &shapeList = ShapeList::instance();

    delete m_backupMemento;
    m_backupMemento = new ShapeListMemento(shapeList.createMemento());
    m_restoreButton->setEnabled(true);
}

void ShapesWindow::onRestoreClicked()
{
    if (m_backupMemento == nullptr) {
        qWarning() << "No backup available to restore.";
        return;
    }

    ShapeList &shapeList = ShapeList::instance();
    shapeList.setMemento(*m_backupMemento);
    if (!shapeList.isEmpty()) {
        shapeList.setCurrentIndex(0);
    }
    displayCurrentShape();
    updateNavigationState();
}

void ShapesWindow::onPreviousClicked()
{
    ShapeList &shapeList = ShapeList::instance();
    if (!shapeList.movePrevious()) {
        return;
    }

    displayCurrentShape();
    updateNavigationState();
}

void ShapesWindow::onNextClicked()
{
    ShapeList &shapeList = ShapeList::instance();
    if (!shapeList.moveNext()) {
        return;
    }

    displayCurrentShape();
    updateNavigationState();
}

void ShapesWindow::updatePropertyState()
{
    const QString shapeType = m_shapeComboBox->currentText();
    const bool needsSecondProperty = m_shapeFactory.hasSecondProperty(shapeType);

    m_property2Label->setEnabled(needsSecondProperty);
    m_property2SpinBox->setEnabled(needsSecondProperty);
}

void ShapesWindow::updateNavigationState()
{
    const ShapeList &shapeList = ShapeList::instance();
    m_previousButton->setEnabled(shapeList.hasPrevious());
    m_nextButton->setEnabled(shapeList.hasNext());
}

void ShapesWindow::displayCurrentShape()
{
    ShapeList &shapeList = ShapeList::instance();
    m_canvas->setShape(shapeList.currentShape());
}

void ShapesWindow::createShapeFromInput()
{
    const QString shapeType = m_shapeComboBox->currentText();
    const int penWidth = m_penWidthSpinBox->value();
    const QColor penColour = toColour(m_penColourComboBox->currentText());
    const QColor fillColour = toColour(m_fillColourComboBox->currentText());
    const int property1 = m_property1SpinBox->value();
    const int property2 = m_property2SpinBox->value();

    Shape *shape = m_shapeFactory.createShape(shapeType,
                                              penWidth,
                                              penColour,
                                              fillColour,
                                              property1,
                                              property2);
    if (shape == nullptr) {
        qWarning() << QString("Failed to create shape from UI input for type: %1").arg(shapeType);
        return;
    }

    ShapeList &shapeList = ShapeList::instance();
    shapeList.addShape(shape);
    displayCurrentShape();
}

void ShapesWindow::loadShapesFromXml()
{
    const QString shapeXmlPath = resolveShapesXmlPath();
    ShapeList &shapeList = ShapeList::instance();

    if (!m_shapeXmlSerializer.loadFromFile(shapeXmlPath, shapeList)) {
        qWarning() << QString("Startup XML load failed: %1").arg(shapeXmlPath);
    }

    displayCurrentShape();
}
