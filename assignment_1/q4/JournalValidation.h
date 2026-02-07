#pragma once

#include <QRegularExpression>
#include <QString>

/// Static valiators for journal/article fields used in UI and model edits.
class JournalValidation
{
public:
    /// Author names: letters, spaces, and hyphens only (e.g. "SZ Mbanjwa-Mlana").
    static bool isValidAuthor(const QString &value);
    /// Titles: words must be all letters or all digits; spaces allowed between words.
    static bool isValidTitle(const QString &value);
    /// Journal titles follow the same rules as article titles.
    static bool isValidJournal(const QString &value);
    /// Page ranges: digits separated by a single hyphen with optional spaces (e.g. "12-15").
    static bool isValidPages(const QString &value);

    /// Regex used by validators for author names.
    static const QRegularExpression kAuthorPattern;
    /// Regex used by validators for article/journal titles.
    static const QRegularExpression kTitlePattern;
    /// Regex used by validators for page ranges.
    static const QRegularExpression kPagesPattern;
};
