#include "ShapeList.h"

#include "Shape.h"

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
