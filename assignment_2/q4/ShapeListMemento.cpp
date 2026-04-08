#include "ShapeListMemento.h"

ShapeListMemento::ShapeListMemento(const QList<ShapeSnapshot> &shapeSnapshots, int currentIndex)
    : m_shapeSnapshots(shapeSnapshots)
    , m_currentIndex(currentIndex)
{
}

const QList<ShapeListMemento::ShapeSnapshot> &ShapeListMemento::getState() const
{
    return m_shapeSnapshots;
}

void ShapeListMemento::setState(const QList<ShapeSnapshot> &shapeSnapshots)
{
    m_shapeSnapshots = shapeSnapshots;
}

int ShapeListMemento::getCurrentIndex() const
{
    return m_currentIndex;
}

void ShapeListMemento::setCurrentIndex(int currentIndex)
{
    m_currentIndex = currentIndex;
}
