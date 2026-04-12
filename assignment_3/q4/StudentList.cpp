#include "StudentList.h"

#include "Student.h"

#include <QMetaType>

StudentList &StudentList::instance()
{
    static StudentList listInstance;
    return listInstance;
}

StudentList::StudentList()
    : QObject(nullptr)
{
    registerMetaTypes();
}

StudentList::~StudentList()
{
    for (StudentsContainer::const_iterator it = m_students.cbegin();
         it != m_students.cend();
         ++it) {
        delete *it;
    }
}

void StudentList::registerMetaTypes()
{
    Student::registerMetaTypes();
    qRegisterMetaType<StudentsContainer>("StudentList::StudentsContainer");
}

void StudentList::addStudent(Student *student)
{
    if (student == nullptr) {
        return;
    }

    m_students.append(student);
}

StudentList::StudentsContainer &StudentList::getStudents()
{
    return m_students;
}

const StudentList::StudentsContainer &StudentList::getStudents() const
{
    return m_students;
}

StudentList::StudentsContainer StudentList::students() const
{
    return m_students;
}

int StudentList::indexOfStudentNumber(const QString &studentNumber) const
{
    for (int index = 0; index < m_students.size(); ++index) {
        const Student *student = m_students.at(index);
        if (student != nullptr && student->getNumber() == studentNumber) {
            return index;
        }
    }

    return -1;
}

Student *StudentList::getStudent(int index) const
{
    if (index < 0 || index >= m_students.size()) {
        return nullptr;
    }

    return m_students.at(index);
}

int StudentList::size() const
{
    return m_students.size();
}
