#include "StudentListXmlSerializer.h"

#include "Student.h"
#include "StudentList.h"
#include "StudentListXmlSchema.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDebug>
#include <QFile>
#include <QIODevice>

bool StudentListXmlSerializer::loadFromFile(const QString &filePath, StudentList &studentList) const
{
    if (filePath.trimmed().isEmpty()) {
        qWarning() << "Student list XML path is empty.";
        return false;
    }

    QFile xmlFile(filePath);
    if (!xmlFile.exists()) {
        return true;
    }

    if (!xmlFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open student list XML file for reading:" << filePath;
        return false;
    }

    QDomDocument document;
    const QDomDocument::ParseResult parseResult = document.setContent(&xmlFile);
    if (!parseResult) {
        qWarning() << "Could not parse student list XML file:" << filePath;
        return false;
    }

    const QDomElement rootElement = document.documentElement();
    if (rootElement.tagName() != QString(StudentListXmlSchema::kRootElement)) {
        qWarning() << "Unexpected root element in student list XML:" << rootElement.tagName();
        return false;
    }

    return true;
}

bool StudentListXmlSerializer::saveToFile(const QString &filePath,
                                          const StudentList &studentList) const
{
    if (filePath.trimmed().isEmpty()) {
        qWarning() << "Student list XML path is empty.";
        return false;
    }

    QDomDocument document;
    QDomElement rootElement = document.createElement(StudentListXmlSchema::kRootElement);
    document.appendChild(rootElement);

    const StudentList::StudentsContainer &students = studentList.getStudents();
    for (int index = 0; index < students.size(); ++index) {
        const Student *student = students.at(index);
        if (student == nullptr) {
            continue;
        }
        appendStudentElement(document, rootElement, *student);
    }

    QFile xmlFile(filePath);
    if (!xmlFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Could not open student list XML file for writing:" << filePath;
        return false;
    }

    const QByteArray xmlBytes = document.toByteArray(2);
    const qint64 bytesWritten = xmlFile.write(xmlBytes);
    if (bytesWritten != xmlBytes.size()) {
        qWarning() << "Could not write student list XML file:" << filePath;
        return false;
    }

    return true;
}

void StudentListXmlSerializer::appendStudentElement(QDomDocument &document,
                                                    QDomElement &rootElement,
                                                    const Student &student) const
{
    QDomElement studentElement = document.createElement(StudentListXmlSchema::kStudentElement);
    rootElement.appendChild(studentElement);

    QDomElement numberElement = document.createElement(StudentListXmlSchema::kNumberElement);
    numberElement.appendChild(document.createTextNode(student.getNumber()));
    studentElement.appendChild(numberElement);

    QDomElement modulesElement = document.createElement(StudentListXmlSchema::kModulesElement);
    studentElement.appendChild(modulesElement);

    const Student::ModulesContainer &modules = student.getModules();
    for (Student::ModulesContainer::const_iterator it = modules.cbegin();
         it != modules.cend();
         ++it) {
        QDomElement moduleElement = document.createElement(StudentListXmlSchema::kModuleElement);
        modulesElement.appendChild(moduleElement);

        QDomElement codeElement = document.createElement(StudentListXmlSchema::kCodeElement);
        codeElement.appendChild(document.createTextNode(it.key()));
        moduleElement.appendChild(codeElement);

        QDomElement markElement = document.createElement(StudentListXmlSchema::kMarkElement);
        markElement.appendChild(document.createTextNode(QString::number(it.value())));
        moduleElement.appendChild(markElement);
    }
}
