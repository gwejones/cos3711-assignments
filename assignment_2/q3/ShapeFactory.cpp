#include "ShapeFactory.h"

#include "Circle.h"
#include "Ellipse.h"
#include "Rectangle.h"
#include "Shape.h"
#include "Square.h"

#include <QMetaClassInfo>
#include <QMetaObject>
#include <QMetaProperty>
#include <QObject>
#include <QString>
#include <QStringList>

static const QList<const QMetaObject *> s_registeredShapeMetaObjects = {
    &Circle::staticMetaObject,
    &Square::staticMetaObject,
    &Ellipse::staticMetaObject,
    &Rectangle::staticMetaObject
};

static QString xmlTypeForMetaObject(const QMetaObject &metaObject)
{
    const int classInfoIndex = metaObject.indexOfClassInfo("ShapeXmlType");
    if (classInfoIndex >= 0) {
        return QString::fromLatin1(metaObject.classInfo(classInfoIndex).value());
    }

    return QString::fromLatin1(metaObject.className());
}

static const QMetaObject *findMetaObjectForType(const QString &shapeType)
{
    for (const QMetaObject *metaObject : s_registeredShapeMetaObjects) {
        if (metaObject == nullptr) {
            continue;
        }

        const QString xmlType = xmlTypeForMetaObject(*metaObject);
        if (shapeType.compare(xmlType, Qt::CaseInsensitive) == 0) {
            return metaObject;
        }
    }

    return nullptr;
}

static bool isRegisteredTypeMetaObject(const QMetaObject &metaObject)
{
    for (const QMetaObject *registeredMetaObject : s_registeredShapeMetaObjects) {
        if (registeredMetaObject == &metaObject) {
            return true;
        }
    }

    return false;
}

Shape *ShapeFactory::createShape(const QString &shapeType,
                                 int penWidth,
                                 const QColor &penColour,
                                 const QColor &fillColour,
                                 int property1,
                                 int property2) const
{
    Shape *shape = createShape(shapeType, nullptr);
    if (shape == nullptr) {
        return nullptr;
    }

    shape->setPenWidth(penWidth);
    shape->setPenColour(penColour);
    shape->setFillColour(fillColour);

    if (!shape->setProperty("property1", property1)) {
        delete shape;
        return nullptr;
    }

    if (hasSecondProperty(shapeType) && !shape->setProperty("property2", property2)) {
        delete shape;
        return nullptr;
    }

    return shape;
}

Shape *ShapeFactory::createShape(const QString &shapeType, QObject *parent) const
{
    const QMetaObject *metaObject = findMetaObjectForType(shapeType);
    if (metaObject == nullptr) {
        return nullptr;
    }

    QObject *object = metaObject->newInstance(Q_ARG(QObject *, parent));
    if (object == nullptr) {
        return nullptr;
    }

    Shape *shape = qobject_cast<Shape *>(object);
    if (shape == nullptr) {
        delete object;
        return nullptr;
    }

    return shape;
}

bool ShapeFactory::isSupportedType(const QString &shapeType) const
{
    return findMetaObjectForType(shapeType) != nullptr;
}

bool ShapeFactory::hasSecondProperty(const QString &shapeType) const
{
    const QMetaObject *metaObject = findMetaObjectForType(shapeType);
    if (metaObject == nullptr) {
        return false;
    }

    return metaObject->indexOfProperty("property2") >= 0;
}

QString ShapeFactory::typeForShape(const Shape *shape) const
{
    if (shape == nullptr) {
        return QString();
    }

    const QMetaObject *metaObject = shape->metaObject();
    while (metaObject != nullptr) {
        if (isRegisteredTypeMetaObject(*metaObject)) {
            return xmlTypeForMetaObject(*metaObject);
        }
        metaObject = metaObject->superClass();
    }

    return QString();
}

QStringList ShapeFactory::supportedTypes() const
{
    QStringList types;

    for (const QMetaObject *metaObject : s_registeredShapeMetaObjects) {
        if (metaObject == nullptr) {
            continue;
        }

        types.append(xmlTypeForMetaObject(*metaObject));
    }

    return types;
}
