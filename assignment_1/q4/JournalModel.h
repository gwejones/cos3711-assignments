#pragma once

#include <QStandardItemModel>

class JournalModel : public QStandardItemModel
{
public:
    /// Model for the journal article dataabse, enforcing year constraints and edit rules.
    explicit JournalModel(QObject *parent = nullptr);

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
};
