#pragma once

#include <QColor>
#include <QString>
#include <QStringList>

class QObject;
class Shape;

/**
 * Factory class that instanciates shape objects from shape type names.
 * Uses Qt meta-object reflection to construct concrete Shape instances.
 */
class ShapeFactory
{
public:
    /**
     * Creates and initializes a shape for the given type name.
     * Returns nullptr if the type is unsupported.
     */
    Shape *createShape(const QString &shapeType,
                       int penWidth,
                       const QColor &penColour,
                       const QColor &fillColour,
                       int property1,
                       int property2) const;

    /**
     * Creates a shape instance for the given type name using its Q_INVOKABLE constructor.
     * Returns nullptr if the type is unsupported or the instance cannot be created.
     */
    Shape *createShape(const QString &shapeType, QObject *parent) const;

    /**
     * Returns true when the type name is registered and can be created by this factory.
     */
    bool isSupportedType(const QString &shapeType) const;

    /**
     * Returns true when the type exposes a second geometric property (property2).
     */
    bool hasSecondProperty(const QString &shapeType) const;

    /**
     * Resolves the XML/runtime type name for a concrete shape instance.
     * Returns an empty string when the shape type is not registered.
     */
    QString typeForShape(const Shape *shape) const;

    /**
     * Returns all supported shape type names.
     */
    QStringList supportedTypes() const;
};
