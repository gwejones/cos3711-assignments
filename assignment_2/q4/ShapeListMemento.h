#pragma once

#include <QColor>
#include <QList>
#include <QString>

class ShapeList;

/**
 * Memento class that stores a ShapeList state snapshot.
 * Only ShapeList (originator) can create and read this state.
 */
class ShapeListMemento
{
public:
private:
    struct ShapeSnapshot
    {
        QString m_shapeType;
        int m_penWidth = 1;
        QColor m_penColour = Qt::black;
        QColor m_fillColour = Qt::white;
        int m_property1 = 1;
        int m_property2 = 1;
        bool m_hasSecondProperty = false;
    };

    ShapeListMemento() = default;
    ShapeListMemento(const QList<ShapeSnapshot> &shapeSnapshots, int currentIndex);

    const QList<ShapeSnapshot> &getState() const;
    void setState(const QList<ShapeSnapshot> &shapeSnapshots);

    int getCurrentIndex() const;
    void setCurrentIndex(int currentIndex);

    QList<ShapeSnapshot> m_shapeSnapshots;
    int m_currentIndex = -1;

    friend class ShapeList;
};
