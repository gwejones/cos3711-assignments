#pragma once

#include <QColor>
#include <QRegularExpression>
#include <QSortFilterProxyModel>

class JournalFilterProxy : public QSortFilterProxyModel
{
public:
    explicit JournalFilterProxy(QObject *parent = nullptr);

    void setFilterField(int column);
    void setWildcardFilter(const QString &pattern);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
    QVariant data(const QModelIndex &index, int role) const override;

private:
    int m_filterColumn = 0;
    QRegularExpression m_filterRegex;
    static const QColor kOldArticleColor;
    static const QColor kRecentArticleColor;
};
