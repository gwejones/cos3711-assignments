#pragma once

#include <QRegularExpression>
#include <QStyledItemDelegate>

/// Delegate that injects regex validation into text editors for table cells.
/// Implements the Delegate OOP design pattren.
class TextValidationDelegate : public QStyledItemDelegate
{
public:
    /// Delegate that attaches a QRegularExpressionValidator to text editors.
    explicit TextValidationDelegate(const QRegularExpression &pattern, QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

private:
    QRegularExpression m_pattern;
};
