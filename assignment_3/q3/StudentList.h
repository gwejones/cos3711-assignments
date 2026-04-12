#pragma once

#include <QList>
#include <QObject>
#include <QString>

class Student;

class StudentList
    : public QObject
{
public:
    typedef QList<Student *> StudentsContainer;

private:
    Q_OBJECT
    Q_PROPERTY(StudentsContainer students READ students)

public:
    static StudentList &instance();

    /**
     * Register StudentList-related types for Qt meta-object reflection.
     */
    static void registerMetaTypes();

    /**
     * Add a student pointer to the list.
     */
    void addStudent(Student *student);

    /**
     * Access the whole list of student pointers.
     * This mutable view allows reflection code to inspect/update the container directly.
     */
    StudentsContainer &getStudents();

    /**
     * Access the whole list of student pointers (read-only).
     */
    const StudentsContainer &getStudents() const;

    /**
     * Property-compatible snapshot of the student container.
     */
    StudentsContainer students() const;

    /**
     * Return the index for a student number, or -1 if not found.
     */
    int indexOfStudentNumber(const QString &studentNumber) const;

    /**
     * Return the student pointer at the given index, or nullptr if invalid.
     */
    Student *getStudent(int index) const;

    /**
     * Return the number of stored students.
     */
    int size() const;

private:
    StudentList();
    ~StudentList() override;

    StudentList(const StudentList &) = delete;             // Prevent copying singleton.
    StudentList &operator=(const StudentList &) = delete;  // Prevent assignment singleton.

    StudentsContainer m_students;
};

Q_DECLARE_METATYPE(StudentList::StudentsContainer)
