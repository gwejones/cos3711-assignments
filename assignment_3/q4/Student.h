#pragma once

#include <QMap>
#include <QObject>
#include <QString>

class Student
    : public QObject
{
public:
    typedef QMap<QString, int> ModulesContainer;

private:
    Q_OBJECT
    Q_PROPERTY(QString number READ getNumber WRITE setNumber)
    Q_PROPERTY(ModulesContainer modules READ getModules WRITE setModules)

public:
    Q_INVOKABLE explicit Student(QObject *parent = nullptr);
    ~Student() override = default;

    /**
     * Register Student-related types for Qt meta-object reflection.
     */
    static void registerMetaTypes();

    /**
     * Set the student number.
     */
    void setNumber(const QString &number);

    /**
     * Get the stored student number.
     */
    QString getNumber() const;

    /**
     * Add or update a module mark for the student.
     */
    void addModule(const QString &moduleCode, int mark);

    /**
     * Access the student's module-mark container.
     */
    const ModulesContainer &getModules() const;

    /**
     * Replace the full module-mark container.
     */
    void setModules(const ModulesContainer &modules);

    /**
     * Calculate the average mark across all stored modules.
     */
    double average() const;

    /**
     * Check whether the student satisfies the graduation rules.
     */
    bool graduate() const;

private:
    QString m_number;
    ModulesContainer m_modules;
};

Q_DECLARE_METATYPE(Student::ModulesContainer)
Q_DECLARE_METATYPE(Student *)
