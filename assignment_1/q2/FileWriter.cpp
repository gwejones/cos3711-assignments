#include "FileWriter.h"
#include "Serializer.h"
#include <QFile>
#include <QTextStream>

FileWriter::FileWriter(QObjectList *olist, QString fname)
    : list(olist)
    , filename(fname)
{
}

int FileWriter::write()
{
    if (!list)
    {
        return 0;
    }

    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream err(stderr);
        err << "Failed to open output file '" << filename
            << "': " << file.errorString() << Qt::endl;
        return 0;
    }

    QTextStream out(&file);
    MetaObjectSerializer serializer;
    int recordsWritten = 0;

    for (QObject *object : *list)
    {
        if (!object)
        {
            continue;
        }
        out << serializer.serialize(object) << Qt::endl;
        recordsWritten++;
    }

    return recordsWritten;
}
