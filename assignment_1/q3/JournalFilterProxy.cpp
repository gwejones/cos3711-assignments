#include "JournalFilterProxy.h"
#include "JournalConstants.h"
#include <QBrush>
#include <QColor>
#include <QDate>

JournalFilterProxy::JournalFilterProxy(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    m_filterColumn = JournalColumns::Author;
}

const QColor JournalFilterProxy::kOldArticleColor = QColor(QStringLiteral("tomato"));
const QColor JournalFilterProxy::kRecentArticleColor = QColor(QStringLiteral("lightgreen"));

void JournalFilterProxy::setFilterField(int column)
{
    m_filterColumn = column;
    invalidateFilter();
}

void JournalFilterProxy::setWildcardFilter(const QString &pattern)
{
    if (pattern.trimmed().isEmpty()) {
        m_filterRegex = QRegularExpression();
    } else {
        const QString regexPattern = QRegularExpression::wildcardToRegularExpression(pattern);
        m_filterRegex = QRegularExpression(regexPattern, QRegularExpression::CaseInsensitiveOption);
    }
    invalidateFilter();
}

bool JournalFilterProxy::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (!m_filterRegex.isValid() || m_filterRegex.pattern().isEmpty()) {
        return true;
    }
    if (m_filterColumn < 0) {
        return true;
    }
    const QModelIndex index = sourceModel()->index(sourceRow, m_filterColumn, sourceParent);
    const QString value = sourceModel()->data(index, Qt::DisplayRole).toString();
    return m_filterRegex.match(value).hasMatch();
}

QVariant JournalFilterProxy::data(const QModelIndex &index, int role) const
{
    if (role == Qt::BackgroundRole && index.isValid()) {
        // Map to the source model to look up the article year and color the row by age.
        const QModelIndex sourceIndex = mapToSource(index);
        const QModelIndex yearIndex = sourceModel()->index(sourceIndex.row(), JournalColumns::Year);
        const int year = sourceModel()->data(yearIndex, Qt::EditRole).toInt();
        if (year > 0) {
            const int currentYear = QDate::currentDate().year();
            const int age = currentYear - year;
            if (age > 10) {
                return QBrush(kOldArticleColor);
            }
            if (age <= 5) {
                return QBrush(kRecentArticleColor);
            }
        }
    }
    return QSortFilterProxyModel::data(index, role);
}
