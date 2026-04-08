#include "ShapeList.h"

#include "Shape.h"
#include "ShapeFactory.h"
#include "ShapeListMemento.h"

#include <QDebug>
#include <QVariant>

ShapeList &ShapeList::instance()
{
    static ShapeList s_instance;
    return s_instance;
}

ShapeList::~ShapeList()
{
    clear();
}

void ShapeList::addShape(Shape *shape)
{
    if (shape == nullptr) {
        return;
    }

    m_shapes.append(shape);
    m_currentIndex = m_shapes.size() - 1;
}

Shape *ShapeList::currentShape() const
{
    if (m_currentIndex < 0 || m_currentIndex >= m_shapes.size()) {
        return nullptr;
    }

    return m_shapes.at(m_currentIndex);
}

Shape *ShapeList::shapeAt(int index) const
{
    if (index < 0 || index >= m_shapes.size()) {
        return nullptr;
    }

    return m_shapes.at(index);
}

bool ShapeList::hasNext() const
{
    return m_currentIndex >= 0 && m_currentIndex < (m_shapes.size() - 1);
}

bool ShapeList::hasPrevious() const
{
    return m_currentIndex > 0 && m_currentIndex < m_shapes.size();
}

bool ShapeList::moveNext()
{
    if (!hasNext()) {
        return false;
    }

    ++m_currentIndex;
    return true;
}

bool ShapeList::movePrevious()
{
    if (!hasPrevious()) {
        return false;
    }

    --m_currentIndex;
    return true;
}

bool ShapeList::setCurrentIndex(int index)
{
    if (index < 0 || index >= m_shapes.size()) {
        return false;
    }

    m_currentIndex = index;
    return true;
}

int ShapeList::size() const
{
    return m_shapes.size();
}

bool ShapeList::isEmpty() const
{
    return m_shapes.isEmpty();
}

int ShapeList::currentIndex() const
{
    return m_currentIndex;
}

void ShapeList::clear()
{
    for (Shape *shape : m_shapes) {
        delete shape;
    }
    m_shapes.clear();
    m_currentIndex = -1;
}

ShapeListMemento ShapeList::createMemento() const
{
    ShapeFactory shapeFactory;
    QList<ShapeListMemento::ShapeSnapshot> shapeSnapshots;

    for (Shape *shape : m_shapes) {
        ShapeListMemento::ShapeSnapshot shapeSnapshot;
        shapeSnapshot.m_shapeType = shapeFactory.typeForShape(shape);
        if (shapeSnapshot.m_shapeType.isEmpty()) {
            qWarning() << "Cannot snapshot shape with unknown runtime type.";
            continue;
        }

        shapeSnapshot.m_penWidth = shape->penWidth();
        shapeSnapshot.m_penColour = shape->penColour();
        shapeSnapshot.m_fillColour = shape->fillColour();

        const QVariant property1Value = shape->property("property1");
        bool isProperty1Int = false;
        shapeSnapshot.m_property1 = property1Value.toInt(&isProperty1Int);
        if (!isProperty1Int || shapeSnapshot.m_property1 <= 0) {
            qWarning() << QString("Cannot snapshot invalid property1 for shape type '%1'.")
                              .arg(shapeSnapshot.m_shapeType);
            continue;
        }

        shapeSnapshot.m_hasSecondProperty = shapeFactory.hasSecondProperty(shapeSnapshot.m_shapeType);
        if (shapeSnapshot.m_hasSecondProperty) {
            const QVariant property2Value = shape->property("property2");
            bool isProperty2Int = false;
            shapeSnapshot.m_property2 = property2Value.toInt(&isProperty2Int);
            if (!isProperty2Int || shapeSnapshot.m_property2 <= 0) {
                qWarning() << QString("Cannot snapshot invalid property2 for shape type '%1'.")
                                  .arg(shapeSnapshot.m_shapeType);
                continue;
            }
        }

        shapeSnapshots.append(shapeSnapshot);
    }

    return ShapeListMemento(shapeSnapshots, m_currentIndex);
}

void ShapeList::setMemento(const ShapeListMemento &memento)
{
    ShapeFactory shapeFactory;
    QList<Shape *> restoredShapes;

    const QList<ShapeListMemento::ShapeSnapshot> &shapeSnapshots = memento.getState();

    for (const ShapeListMemento::ShapeSnapshot &shapeSnapshot : shapeSnapshots) {
        if (!shapeFactory.isSupportedType(shapeSnapshot.m_shapeType)) {
            qWarning() << QString("Cannot restore unsupported shape type '%1'.")
                              .arg(shapeSnapshot.m_shapeType);
            // Clean up partially reconstructed shapes in case of failed restore.
            for (Shape *shape : restoredShapes) {
                delete shape;
            }
            return;
        }

        const int property2 = shapeSnapshot.m_hasSecondProperty ? shapeSnapshot.m_property2 : 1;
        Shape *shape = shapeFactory.createShape(shapeSnapshot.m_shapeType,
                                                shapeSnapshot.m_penWidth,
                                                shapeSnapshot.m_penColour,
                                                shapeSnapshot.m_fillColour,
                                                shapeSnapshot.m_property1,
                                                property2);
        if (shape == nullptr) {
            qWarning() << QString("Failed to restore shape type '%1' from memento.")
                              .arg(shapeSnapshot.m_shapeType);
            // Clean up partially reconstructed shapes in case of failed restore.
            for (Shape *restoredShape : restoredShapes) {
                delete restoredShape;
            }
            return;
        }

        restoredShapes.append(shape);
    }

    clear();

    for (Shape *shape : restoredShapes) {
        m_shapes.append(shape);
    }

    const int targetIndex = memento.getCurrentIndex();
    if (m_shapes.isEmpty()) {
        m_currentIndex = -1;
    } else if (targetIndex < 0 || targetIndex >= m_shapes.size()) {
        m_currentIndex = 0;
    } else {
        m_currentIndex = targetIndex;
    }
}
