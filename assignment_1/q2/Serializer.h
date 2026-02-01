#pragma once

#include <QObject>
#include <QString>

class Serializer
{
public:
    virtual ~Serializer() = default;
    virtual QString serialize(const QObject *object) const = 0;
};

class MetaObjectSerializer : public Serializer
{
public:
    QString serialize(const QObject *object) const override;
};
