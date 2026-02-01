#pragma once

#include <QObject>
#include <QString>

// Abstract interfce for turning QObject instaces into text records.
class Serializer
{
public:
    // Virtual destructor.
    virtual ~Serializer();
    // Serializes an object to a single-line string; returns empty if object is null.
    virtual QString serialize(const QObject *object) const = 0;
};

// Serializer implementation that uses Qt's meta-object system to emit key/value pairs.
class MetaObjectSerializer : public Serializer
{
public:
    // Builds "type=ClassName,prop=value,..." from meta-properties.
    QString serialize(const QObject *object) const override;
};
