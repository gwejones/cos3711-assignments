#pragma once

#include <QList>
#include <QString>

class QDomDocument;
class QDomElement;
class Student;
class StudentList;

class StudentListXmlSerializer
{
public:
    /**
     * Load StudentList data from the given XML file path.
     * Returns true when loading succeeds or when the file does not exist.
     */
    bool loadFromFile(const QString &filePath, StudentList &studentList) const;

    /**
     * Save StudentList data to the given XML file path.
     * Returns true when the XML document is written successfully.
     */
    bool saveToFile(const QString &filePath, const StudentList &studentList) const;

private:
    void deleteStudents(QList<Student *> &students) const;
    bool parseModuleElement(const QDomElement &moduleElement, QString &moduleCode, int &mark) const;
    bool parseStudentElement(const QDomElement &studentElement, Student *&student) const;
    void appendStudentElement(QDomDocument &document,
                              QDomElement &rootElement,
                              const Student &student) const;
};
