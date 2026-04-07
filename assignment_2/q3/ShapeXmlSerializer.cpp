#include "ShapeXmlSerializer.h"

#include "Shape.h"
#include "ShapeList.h"

#include <QColor>
#include <QDebug>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QFile>
#include <QMetaObject>
#include <QMetaProperty>
#include <QObject>
#include <QString>
#include <QVariant>

static constexpr const char *kRootElementName = "shapeList";
static constexpr const char *kShapeElementName = "shape";
static constexpr const char *kAttributeType = "type";
static constexpr const char *kAttributePenWidth = "pw";
static constexpr const char *kAttributePenColour = "pc";
static constexpr const char *kAttributeFillColour = "fc";
static constexpr const char *kAttributeProperty1 = "p1";
static constexpr const char *kAttributeProperty2 = "p2";

static void deleteShapes(QList<Shape *> &shapes)
{
    for (Shape *shape : shapes) {
        delete shape;
    }
    shapes.clear();
}

bool ShapeXmlSerializer::loadFromFile(const QString &filePath,
                                      ShapeList &shapeList) const
{
    if (filePath.trimmed().isEmpty()) {
        qWarning() << "Shape XML path is empty.";
        return false;
    }

    QFile xmlFile(filePath);
    if (!xmlFile.exists()) {
        qWarning() << QString("Shape XML file not found: %1").arg(filePath);
        return false;
    }

    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << QString("Failed to open shape XML file for reading: %1").arg(filePath);
        return false;
    }

    QDomDocument document;
    const QDomDocument::ParseResult parseResult = document.setContent(&xmlFile);
    if (!parseResult) {
        qWarning() << QString("Failed to parse shape XML at line %1, column %2: %3")
                     .arg(parseResult.errorLine)
                     .arg(parseResult.errorColumn)
                     .arg(parseResult.errorMessage);
        return false;
    }

    const QDomElement rootElement = document.documentElement();
    if (rootElement.isNull() || rootElement.tagName() != kRootElementName) {
        qWarning() << "Invalid XML root element. Expected <shapeList>.";
        return false;
    }

    QList<Shape *> loadedShapes;

    QDomNode childNode = rootElement.firstChild();
    while (!childNode.isNull()) {
        if (childNode.isElement()) {
            const QDomElement shapeElement = childNode.toElement();
            if (shapeElement.tagName() != kShapeElementName) {
                qWarning() << "Unexpected XML element found. Only <shape> is allowed inside <shapeList>.";
                deleteShapes(loadedShapes);
                return false;
            }

            Shape *shape = nullptr;
            if (!deserializeShapeElement(shapeElement, shape)) {
                deleteShapes(loadedShapes);
                return false;
            }

            loadedShapes.append(shape);
        }

        childNode = childNode.nextSibling();
    }

    shapeList.clear();
    for (Shape *shape : loadedShapes) {
        shapeList.addShape(shape);
    }

    if (!shapeList.isEmpty()) {
        shapeList.setCurrentIndex(0);
    }

    return true;
}

bool ShapeXmlSerializer::saveToFile(const QString &filePath,
                                    const ShapeList &shapeList) const
{
    if (filePath.trimmed().isEmpty()) {
        qWarning() << "Shape XML path is empty.";
        return false;
    }

    QDomDocument document;
    QDomElement rootElement = document.createElement(kRootElementName);
    document.appendChild(rootElement);

    for (int index = 0; index < shapeList.size(); ++index) {
        Shape *shape = shapeList.shapeAt(index);
        if (shape == nullptr) {
            qWarning() << QString("Shape at index %1 is null.").arg(index);
            return false;
        }

        QDomElement shapeElement = document.createElement(kShapeElementName);
        if (!serializeShapeElement(*shape, shapeElement)) {
            return false;
        }

        rootElement.appendChild(shapeElement);
    }

    QFile xmlFile(filePath);
    if (!xmlFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qWarning() << QString("Failed to open shape XML file for writing: %1").arg(filePath);
        return false;
    }

    const QByteArray xmlBytes = document.toByteArray(2);
    const qint64 bytesWritten = xmlFile.write(xmlBytes);
    if (bytesWritten != xmlBytes.size()) {
        qWarning() << QString("Failed to write complete XML output to: %1").arg(filePath);
        return false;
    }

    return true;
}

bool ShapeXmlSerializer::deserializeShapeElement(const QDomElement &shapeElement,
                                                 Shape *&shape) const
{
    shape = nullptr;

    QString shapeType;
    QString penWidthText;
    QString penColourText;
    QString fillColourText;
    QString property1Text;
    QString property2Text;

    if (!readRequiredAttribute(shapeElement, kAttributeType, &shapeType)
        || !readRequiredAttribute(shapeElement, kAttributePenWidth, &penWidthText)
        || !readRequiredAttribute(shapeElement, kAttributePenColour, &penColourText)
        || !readRequiredAttribute(shapeElement, kAttributeFillColour, &fillColourText)
        || !readRequiredAttribute(shapeElement, kAttributeProperty1, &property1Text)
        || !readRequiredAttribute(shapeElement, kAttributeProperty2, &property2Text)) {
        return false;
    }

    if (!m_shapeFactory.isSupportedType(shapeType)) {
        qWarning() << QString("Unsupported shape type in XML: %1").arg(shapeType);
        return false;
    }

    int penWidth = 0;
    int property1 = 0;
    int property2 = 1;
    QColor penColour;
    QColor fillColour;

    if (!parsePositiveInt(penWidthText, kAttributePenWidth, &penWidth)
        || !parseColour(penColourText, kAttributePenColour, &penColour)
        || !parseColour(fillColourText, kAttributeFillColour, &fillColour)
        || !parsePositiveInt(property1Text, kAttributeProperty1, &property1)) {
        return false;
    }

    const bool requiresSecondProperty = m_shapeFactory.hasSecondProperty(shapeType);
    const QString property2Trimmed = property2Text.trimmed();

    if (requiresSecondProperty) {
        if (property2Trimmed.isEmpty()) {
            qWarning() << QString("Attribute '%1' must contain a positive integer for type '%2'.")
                         .arg(kAttributeProperty2)
                         .arg(shapeType);
            return false;
        }

        if (!parsePositiveInt(property2Trimmed, kAttributeProperty2, &property2)) {
            return false;
        }
    } else if (!property2Trimmed.isEmpty()) {
        int ignoredValue = 0;
        if (!parsePositiveInt(property2Trimmed, kAttributeProperty2, &ignoredValue)) {
            return false;
        }
    }

    Shape *createdShape = m_shapeFactory.createShape(shapeType,
                                                     penWidth,
                                                     penColour,
                                                     fillColour,
                                                     property1,
                                                     property2);
    if (createdShape == nullptr) {
        qWarning() << QString("Failed to instantiate shape type: %1").arg(shapeType);
        return false;
    }

    shape = createdShape;
    return true;
}

bool ShapeXmlSerializer::serializeShapeElement(const Shape &shape,
                                               QDomElement &shapeElement) const
{
    const QString shapeType = m_shapeFactory.typeForShape(&shape);
    if (shapeType.isEmpty()) {
        qWarning() << "Cannot serialize shape with unknown runtime type.";
        return false;
    }

    int property1 = 0;
    if (!readIntegerProperty(shape, "property1", &property1)) {
        qWarning() << QString("Failed to read property1 for shape type '%1'.").arg(shapeType);
        return false;
    }

    const bool hasProperty2Value = hasProperty(shape, "property2");
    int property2 = 0;
    if (hasProperty2Value && !readIntegerProperty(shape, "property2", &property2)) {
        qWarning() << QString("Failed to read property2 for shape type '%1'.").arg(shapeType);
        return false;
    }

    QColor penColour;
    QColor fillColour;
    if (!readColourProperty(shape, "penColour", &penColour)
        || !readColourProperty(shape, "fillColour", &fillColour)) {
        qWarning() << QString("Failed to read colour properties for shape type '%1'.").arg(shapeType);
        return false;
    }

    shapeElement.setAttribute(kAttributeType, shapeType);
    shapeElement.setAttribute(kAttributePenWidth, QString::number(shape.penWidth()));
    shapeElement.setAttribute(kAttributePenColour, toXmlColour(penColour));
    shapeElement.setAttribute(kAttributeFillColour, toXmlColour(fillColour));
    shapeElement.setAttribute(kAttributeProperty1, QString::number(property1));
    shapeElement.setAttribute(kAttributeProperty2, hasProperty2Value ? QString::number(property2) : QString());

    return true;
}

bool ShapeXmlSerializer::readRequiredAttribute(const QDomElement &element,
                                          const QString &name,
                                          QString *value)
{
    if (!element.hasAttribute(name)) {
        qWarning() << QString("Missing required attribute '%1' in <shape> element.").arg(name);
        return false;
    }

    *value = element.attribute(name);
    return true;
}

bool ShapeXmlSerializer::parsePositiveInt(const QString &text,
                                          const QString &attributeName,
                                          int *value)
{
    const QString trimmed = text.trimmed();
    bool isInteger = false;
    const int parsedValue = trimmed.toInt(&isInteger);

    if (!isInteger || parsedValue <= 0) {
        qWarning() << QString("Attribute '%1' must be a positive integer.").arg(attributeName);
        return false;
    }

    *value = parsedValue;
    return true;
}

bool ShapeXmlSerializer::parseColour(const QString &text,
                                     const QString &attributeName,
                                     QColor *colour)
{
    const QColor parsedColour(text.trimmed());
    if (!parsedColour.isValid()) {
        qWarning() << QString("Attribute '%1' contains an invalid colour value: %2")
                     .arg(attributeName)
                     .arg(text);
        return false;
    }

    *colour = parsedColour;
    return true;
}

bool ShapeXmlSerializer::hasProperty(const QObject &object, const char *propertyName)
{
    return object.metaObject()->indexOfProperty(propertyName) >= 0;
}

bool ShapeXmlSerializer::readIntegerProperty(const QObject &object,
                                             const char *propertyName,
                                             int *value)
{
    if (!hasProperty(object, propertyName)) {
        return false;
    }

    const QVariant propertyValue = object.property(propertyName);
    if (!propertyValue.isValid()) {
        return false;
    }

    bool isInteger = false;
    const int parsedValue = propertyValue.toInt(&isInteger);
    if (!isInteger) {
        return false;
    }

    *value = parsedValue;
    return true;
}

bool ShapeXmlSerializer::readColourProperty(const QObject &object,
                                            const char *propertyName,
                                            QColor *colour)
{
    if (!hasProperty(object, propertyName)) {
        return false;
    }

    const QVariant propertyValue = object.property(propertyName);
    if (!propertyValue.isValid() || !propertyValue.canConvert<QColor>()) {
        return false;
    }

    const QColor parsedColour = propertyValue.value<QColor>();
    if (!parsedColour.isValid()) {
        return false;
    }

    *colour = parsedColour;
    return true;
}

QString ShapeXmlSerializer::toXmlColour(const QColor &colour)
{
    if (colour == QColor(Qt::black)) {
        return "Black";
    }
    if (colour == QColor(Qt::blue)) {
        return "Blue";
    }
    if (colour == QColor(Qt::green)) {
        return "Green";
    }
    if (colour == QColor(Qt::red)) {
        return "Red";
    }

    return colour.name(QColor::HexRgb);
}
