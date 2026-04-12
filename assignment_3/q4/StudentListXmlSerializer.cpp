#include "StudentListXmlSerializer.h"

#include "Student.h"
#include "StudentList.h"
#include "StudentListXmlSchema.h"

#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDebug>
#include <QFile>
#include <QIODevice>

void StudentListXmlSerializer::deleteStudents(QList<Student *> &students) const
{
    for (QList<Student *>::const_iterator it = students.cbegin();
         it != students.cend();
         ++it) {
        delete *it;
    }
    students.clear();
}

bool StudentListXmlSerializer::parseModuleElement(const QDomElement &moduleElement,
                                                  QString &moduleCode,
                                                  int &mark) const
{
    if (moduleElement.tagName() != QString(StudentListXmlSchema::kModuleElement)) {
        qWarning() << "Unexpected element inside <modules>:" << moduleElement.tagName();
        return false;
    }

    const QDomElement codeElement = moduleElement.firstChildElement(StudentListXmlSchema::kCodeElement);
    if (codeElement.isNull()) {
        qWarning() << "Missing <code> element in <module>.";
        return false;
    }

    moduleCode = codeElement.text().trimmed();
    if (moduleCode.isEmpty()) {
        qWarning() << "Module code cannot be empty.";
        return false;
    }

    const QDomElement markElement = moduleElement.firstChildElement(StudentListXmlSchema::kMarkElement);
    if (markElement.isNull()) {
        qWarning() << "Missing <mark> element in <module>.";
        return false;
    }

    const QString markText = markElement.text().trimmed();
    bool isMarkNumber = false;
    mark = markText.toInt(&isMarkNumber);
    if (!isMarkNumber) {
        qWarning() << "Module mark must be numeric.";
        return false;
    }

    return true;
}

bool StudentListXmlSerializer::parseStudentElement(const QDomElement &studentElement,
                                                   Student *&student) const
{
    student = nullptr;
    if (studentElement.tagName() != QString(StudentListXmlSchema::kStudentElement)) {
        qWarning() << "Unexpected element inside <StudentList>:" << studentElement.tagName();
        return false;
    }

    const QDomElement numberElement =
        studentElement.firstChildElement(StudentListXmlSchema::kNumberElement);
    if (numberElement.isNull()) {
        qWarning() << "Missing <number> element in <student>.";
        return false;
    }

    const QString studentNumber = numberElement.text().trimmed();
    if (studentNumber.isEmpty()) {
        qWarning() << "Student number cannot be empty.";
        return false;
    }

    const QDomElement modulesElement =
        studentElement.firstChildElement(StudentListXmlSchema::kModulesElement);
    if (modulesElement.isNull()) {
        qWarning() << "Missing <modules> element in <student>.";
        return false;
    }

    Student *parsedStudent = new Student();
    parsedStudent->setNumber(studentNumber);

    QDomNode moduleNode = modulesElement.firstChild();
    while (!moduleNode.isNull()) {
        if (moduleNode.isElement()) {
            const QDomElement moduleElement = moduleNode.toElement();

            QString moduleCode;
            int mark = 0;
            const bool isValidModule = parseModuleElement(moduleElement, moduleCode, mark);
            if (!isValidModule) {
                delete parsedStudent;
                return false;
            }

            parsedStudent->addModule(moduleCode, mark);
        }

        moduleNode = moduleNode.nextSibling();
    }

    student = parsedStudent;
    return true;
}

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

    StudentList::StudentsContainer parsedStudents;

    QDomNode childNode = rootElement.firstChild();
    while (!childNode.isNull()) {
        if (childNode.isElement()) {
            const QDomElement studentElement = childNode.toElement();

            Student *student = nullptr;
            const bool isValidStudent = parseStudentElement(studentElement, student);
            if (!isValidStudent) {
                deleteStudents(parsedStudents);
                return false;
            }

            parsedStudents.append(student);
        }

        childNode = childNode.nextSibling();
    }

    StudentList::StudentsContainer &existingStudents = studentList.getStudents();
    deleteStudents(existingStudents);
    for (StudentList::StudentsContainer::const_iterator it = parsedStudents.cbegin();
         it != parsedStudents.cend();
         ++it) {
        existingStudents.append(*it);
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
