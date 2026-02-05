#include "SpinBoxDelegate.h"

#include <QAbstractItemModel>
#include <QSpinBox>

SpinBoxDelegate::SpinBoxDelegate(int minValue, int maxValue, QObject *parent)
    : QStyledItemDelegate(parent)
    , m_minValue(minValue)
    , m_maxValue(maxValue)
{
}

QWidget *SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &,
                                       const QModelIndex &) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setRange(m_minValue, m_maxValue);
    return editor;
}

void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);
    spinBox->setValue(value);
}

void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QSpinBox *spinBox = qobject_cast<QSpinBox *>(editor);
    spinBox->interpretText();
    model->setData(index, spinBox->value(), Qt::EditRole);
}
