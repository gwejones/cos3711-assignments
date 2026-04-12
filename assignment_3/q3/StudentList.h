#pragma once

#include <QList>
#include <QString>

class Student;

class StudentList
{
public:
    static StudentList &instance();

    /**
     * Add a student pointer to the list.
     */
    void addStudent(Student *student);

    /**
     * Access the whole list of student pointers.
     */
    const QList<Student *> &getStudents() const;

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
    ~StudentList();

    StudentList(const StudentList &) = delete;             // Prevent copying singleton.
    StudentList &operator=(const StudentList &) = delete;  // Prevent assignment singleton.

    QList<Student *> *m_students = nullptr;
};
