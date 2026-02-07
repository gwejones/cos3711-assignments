#include "JournalValidation.h"

const QRegularExpression JournalValidation::kTitlePattern(
    QStringLiteral("^(?:[A-Za-z]+|[0-9]+)(?: +(?:[A-Za-z]+|[0-9]+))*$"));
const QRegularExpression JournalValidation::kAuthorPattern(
    QStringLiteral("^[A-Za-z]+(?:-[A-Za-z]+)*(?: [A-Za-z]+(?:-[A-Za-z]+)*)*$"));
const QRegularExpression JournalValidation::kPagesPattern(QStringLiteral("^\\d+\\s*-\\s*\\d+$"));

bool JournalValidation::isValidTitle(const QString &value)
{
    const QString trimmed = value.trimmed();
    if (trimmed.isEmpty()) {
        return false;
    }
    return kTitlePattern.match(trimmed).hasMatch();
}

bool JournalValidation::isValidAuthor(const QString &value)
{
    const QString trimmed = value.trimmed();
    if (trimmed.isEmpty()) {
        return false;
    }
    return kAuthorPattern.match(trimmed).hasMatch();
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
    return kPagesPattern.match(trimmed).hasMatch();
}
