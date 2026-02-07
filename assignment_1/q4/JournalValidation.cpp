#include "JournalValidation.h"
#include <QRegularExpression>

bool JournalValidation::isValidTitle(const QString &value)
{
    const QString trimmed = value.trimmed();
    if (trimmed.isEmpty()) {
        return false;
    }
    static const QRegularExpression pattern(
        QStringLiteral("^(?:[A-Za-z]+|[0-9]+)(?: +(?:[A-Za-z]+|[0-9]+))*$"));
    return pattern.match(trimmed).hasMatch();
}

bool JournalValidation::isValidAuthor(const QString &value)
{
    const QString trimmed = value.trimmed();
    if (trimmed.isEmpty()) {
        return false;
    }
    static const QRegularExpression pattern(
        QStringLiteral("^[A-Za-z]+(?:-[A-Za-z]+)*(?: [A-Za-z]+(?:-[A-Za-z]+)*)*$"));
    return pattern.match(trimmed).hasMatch();
}

bool JournalValidation::isValidJournal(const QString &value)
{
    return isValidTitle(value);
}

bool JournalValidation::isValidPages(const QString &value)
{
    const QString trimmed = value.trimmed();
    if (trimmed.isEmpty()) {
        return false;
    }
    static const QRegularExpression pattern(QStringLiteral("^\\d+\\s*-\\s*\\d+$"));
    return pattern.match(trimmed).hasMatch();
}
