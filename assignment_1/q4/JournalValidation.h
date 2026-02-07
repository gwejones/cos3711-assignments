#pragma once

#include <QString>

class JournalValidation
{
public:
    static bool isValidAuthor(const QString &value);
    static bool isValidTitle(const QString &value);
    static bool isValidJournal(const QString &value);
    static bool isValidPages(const QString &value);
};
