#pragma once

#include <QString>

class QDomDocument;
class QDomElement;
class Student;
class StudentList;

class StudentListXmlSerializer
{
public:
    bool loadFromFile(const QString &filePath, StudentList &studentList) const;
    bool saveToFile(const QString &filePath, const StudentList &studentList) const;

private:
    void appendStudentElement(QDomDocument &document,
                              QDomElement &rootElement,
                              const Student &student) const;
};
