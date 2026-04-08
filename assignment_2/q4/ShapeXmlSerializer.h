#pragma once

#include "ShapeFactory.h"

#include <QString>

class QColor;
class QDomElement;
class QObject;
class Shape;
class ShapeList;

/**
 * Loads and saves Shape data in XML (DOM) format with input validation.
 * Uses ShapeFactory to instatiate concrete shape types during deserialization.
 */
class ShapeXmlSerializer
{
public:
    /**
     * Loads shapes from an XML file into the provided ShapeList.
     * Replaces existing list contents only when the full XML load succeeds.
     * Returns true on success, otherwise false and logs details via qWarning().
     */
    bool loadFromFile(const QString &filePath,
                      ShapeList &shapeList) const;

    /**
     * Saves all shapes in the provided ShapeList to an XML file.
     * Returns true on success, otherwise false and logs details via qWarning().
     */
    bool saveToFile(const QString &filePath,
                    const ShapeList &shapeList) const;

private:
    bool deserializeShapeElement(const QDomElement &shapeElement,
                                 Shape *&shape) const;
    bool serializeShapeElement(const Shape &shape,
                               QDomElement &shapeElement) const;

    static bool readRequiredAttribute(const QDomElement &element,
                                 const QString &name,
                                 QString *value);
    static bool parsePositiveInt(const QString &text,
                                 const QString &attributeName,
                                 int *value);
    static bool parseColour(const QString &text,
                            const QString &attributeName,
                            QColor *colour);
    static bool hasProperty(const QObject &object, const char *propertyName);
    static bool readIntegerProperty(const QObject &object,
                                    const char *propertyName,
                                    int *value);
    static bool readColourProperty(const QObject &object,
                                   const char *propertyName,
                                   QColor *colour);
    static QString toXmlColour(const QColor &colour);

    ShapeFactory m_shapeFactory;
};
