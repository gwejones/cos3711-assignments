#pragma once

#include <QList>

class Shape;

/**
 * Singleton manager for the application's single list of Shape instances.
 * Owns the shapes in a QList and tracks the current position for navigation.
 */
class ShapeList
{
public:
    static ShapeList &instance();
    ~ShapeList();

    void addShape(Shape *shape);
    Shape *currentShape() const;
    Shape *shapeAt(int index) const;

    bool hasNext() const;
    bool hasPrevious() const;
    bool moveNext();
    bool movePrevious();
    bool setCurrentIndex(int index);

    int size() const;
    bool isEmpty() const;
    int currentIndex() const;

    void clear();

    ShapeList(const ShapeList &) = delete; // Prevents copy construction.
    ShapeList &operator=(const ShapeList &) = delete; // Prevents copy assignment.
    ShapeList(ShapeList &&) = delete; // Prevents move construction.
    ShapeList &operator=(ShapeList &&) = delete; // Prevents move assignment.

private:
    ShapeList() = default;

    QList<Shape *> m_shapes;
    int m_currentIndex = -1;
};
