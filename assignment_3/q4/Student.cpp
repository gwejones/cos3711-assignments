#include "Student.h"

#include <QMetaType>

static constexpr int kMinimumPassingMark = 50;
static constexpr int kRequiredPassedModuleCount = 5;
static constexpr int kMaximumFirstYearModules = 2;
static constexpr int kMinimumThirdYearModules = 1;
static constexpr int kModuleYearDigitIndex = 3;

Student::Student(QObject *parent)
    : QObject(parent)
{
}

void Student::registerMetaTypes()
{
    qRegisterMetaType<ModulesContainer>("Student::ModulesContainer");
    qRegisterMetaType<Student *>("Student*");
}

void Student::setNumber(const QString &number)
{
    m_number = number;
}

QString Student::getNumber() const
{
    return m_number;
}

void Student::addModule(const QString &moduleCode, int mark)
{
    m_modules[moduleCode] = mark;
}

const Student::ModulesContainer &Student::getModules() const
{
    return m_modules;
}

void Student::setModules(const ModulesContainer &modules)
{
    m_modules = modules;
}

double Student::average() const
{
    if (m_modules.isEmpty()) {
        return 0.0;
    }

    int total = 0;
    for (Student::ModulesContainer::const_iterator it = m_modules.cbegin();
         it != m_modules.cend();
         ++it) {
        total += it.value();
    }

    return static_cast<double>(total) / m_modules.size();
}

bool Student::graduate() const
{
    int passedModules = 0;
    int firstYearModules = 0;
    int thirdYearModules = 0;

    for (Student::ModulesContainer::const_iterator it = m_modules.cbegin();
         it != m_modules.cend();
         ++it) {
        const int mark = it.value();
        if (mark < kMinimumPassingMark) {
            continue;
        }

        ++passedModules;

        const QString moduleCode = it.key();
        if (moduleCode.size() <= kModuleYearDigitIndex) {
            continue;
        }

        const QChar yearDigit = moduleCode.at(kModuleYearDigitIndex);
        if (yearDigit == QChar('1')) {
            ++firstYearModules;
        } else if (yearDigit == QChar('3')) {
            ++thirdYearModules;
        }
    }

    return passedModules >= kRequiredPassedModuleCount
        && firstYearModules <= kMaximumFirstYearModules
        && thirdYearModules >= kMinimumThirdYearModules;
}
