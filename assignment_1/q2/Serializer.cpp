#include "Serializer.h"
#include <QMetaObject>
#include <QMetaProperty>
#include <QStringList>
#include <QVariant>

QString MetaObjectSerializer::serialize(const QObject *object) const
{
    if (!object)
    {
        return QString();
    }

    const QMetaObject *meta = object->metaObject();
    QStringList parts;
    parts << QStringLiteral("type=%1").arg(meta->className());

    // Skip QObject's built-in properties and only serialize properties added by our classes.
    const int start = QObject::staticMetaObject.propertyCount();
    const int end = meta->propertyCount();
    for (int i = start; i < end; ++i)
    {
        const QMetaProperty prop = meta->property(i);
        if (!prop.isReadable())
        {
            continue;
        }
        const QVariant value = object->property(prop.name());
        parts << QStringLiteral("%1=%2").arg(prop.name(), value.toString());
    }

    return parts.join(',');
}

Serializer::~Serializer()
{
}
