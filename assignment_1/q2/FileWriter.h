#pragma once

#include <QObject>
#include <QString>

// Writes serialized QObject data to a text file using the seralizer pattern.
class FileWriter
{
public:
    // Stores the list pointer and output filename.
    FileWriter(QObjectList *olist, QString fname);
    // Serializes each object and writes the output to file; returns number of records written.
    int write();

private:
    QObjectList *list = nullptr;
    QString filename;
};
