#pragma once

#include <QList>

class Shape;
class ShapeListMemento;

/**
 * Singleton manager for the application's single list of Shape instances.
 * Owns the shapes in a QList and tracks the current position for navigation.
 */
class ShapeList
{
public:
    /**
     * Returns the singleton ShapeList instance.
     */
    static ShapeList &instance();

    /**
     * Destroys the list and releases all owned Shape objects.
     */
    ~ShapeList();

    /**
     * Appends a shape to the list and makes it the current shape.
     */
    void addShape(Shape *shape);

    /**
     * Returns the currently selected shape, or nullptr when no valid selection exists.
     */
    Shape *currentShape() const;

    /**
     * Returns the shape at the given index, or nullptr when the index is out of bounds.
     */
    Shape *shapeAt(int index) const;

    /**
     * Returns true when there is a shape after the current selection.
     */
    bool hasNext() const;

    /**
     * Returns true when there is a shape before the current selection.
     */
    bool hasPrevious() const;

    /**
     * Advances selection to the next shape when possible.
     * Returns true when selection changed.
     */
    bool moveNext();

    /**
     * Moves selection to the previous shape when possible.
     * Returns true when selection changed.
     */
    bool movePrevious();

    /**
     * Sets the current selection to the given index.
     * Returns true when the index is valid and selection changed.
     */
    bool setCurrentIndex(int index);

    /**
     * Returns the number of shapes currently stored.
     */
    int size() const;

    /**
     * Returns true when the list contains no shapes.
     */
    bool isEmpty() const;

    /**
     * Returns the current selection index, or -1 when there is no selection.
     */
    int currentIndex() const;

    /**
     * Deletes all stored shapes and resets selection to an empty state.
     */
    void clear();

    /**
     * Creates a memento snapshot for this originator.
     */
    ShapeListMemento createMemento() const;

    /**
     * Restores originator state from a memento.
     */
    void setMemento(const ShapeListMemento &memento);

    ShapeList(const ShapeList &) = delete; // Prevents copy construction.
    ShapeList &operator=(const ShapeList &) = delete; // Prevents copy assignment.
    ShapeList(ShapeList &&) = delete; // Prevents move construction.
    ShapeList &operator=(ShapeList &&) = delete; // Prevents move assignment.

private:
    ShapeList() = default;

    QList<Shape *> m_shapes;
    int m_currentIndex = -1;
};
