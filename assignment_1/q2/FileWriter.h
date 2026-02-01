#pragma once

#include <QObject>
#include <QString>

class FileWriter
{
public:
    FileWriter(QObjectList *olist, QString fname);
    int write();

private:
    QObjectList *list = nullptr;
    QString filename;
};
