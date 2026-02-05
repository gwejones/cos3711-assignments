#pragma once

#include <QStandardItemModel>

class JournalModel : public QStandardItemModel
{
public:
    explicit JournalModel(QObject *parent = nullptr);

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
};
