#pragma once

#include <QStyledItemDelegate>

class SpinBoxDelegate : public QStyledItemDelegate
{
public:
    SpinBoxDelegate(int minValue, int maxValue, QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

private:
    int m_minValue;
    int m_maxValue;
};
