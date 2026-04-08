#include "ShapeList.h"

#include "Shape.h"
#include "ShapeListMemento.h"

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
    ShapeListMemento memento;
    memento.setCurrentIndex(m_currentIndex);
    return memento;
}

void ShapeList::setMemento(const ShapeListMemento &memento)
{
    const int targetIndex = memento.getCurrentIndex();

    if (m_shapes.isEmpty()) {
        m_currentIndex = -1;
        return;
    }

    if (targetIndex < 0 || targetIndex >= m_shapes.size()) {
        m_currentIndex = 0;
        return;
    }

    m_currentIndex = targetIndex;
}
