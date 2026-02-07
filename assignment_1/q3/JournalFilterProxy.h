#pragma once

#include <QColor>
#include <QRegularExpression>
#include <QSortFilterProxyModel>

class JournalFilterProxy : public QSortFilterProxyModel
{
public:
    /// Proxy (OOP Proxy pattern) that filters/sorts a source model and decorates rows based on age.
    explicit JournalFilterProxy(QObject *parent = nullptr);

    void setFilterField(int column);
    void setWildcardFilter(const QString &pattern);

protected:
    /// Override default proxy filtering to apply the wildcard regex to the selected column.
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    /// Overide to customise background for age-based highlighting.
    QVariant data(const QModelIndex &index, int role) const override;

private:
    int m_filterColumn = 0;
    QRegularExpression m_filterRegex;
    static const QColor kOldArticleColor;
    static const QColor kRecentArticleColor;
};
