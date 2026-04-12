#pragma once

#include <QMap>
#include <QString>

class Student
{
public:
    typedef QMap<QString, int> ModulesContainer;

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
