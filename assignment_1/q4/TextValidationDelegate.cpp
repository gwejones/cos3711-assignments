#include "TextValidationDelegate.h"
#include <QLineEdit>
#include <QRegularExpressionValidator>

TextValidationDelegate::TextValidationDelegate(const QRegularExpression &pattern, QObject *parent)
    : QStyledItemDelegate(parent)
    , m_pattern(pattern)
{
}

QWidget *TextValidationDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &,
                                              const QModelIndex &) const
{
    QLineEdit *editor = new QLineEdit(parent);
    editor->setValidator(new QRegularExpressionValidator(m_pattern, editor));
    return editor;
}
