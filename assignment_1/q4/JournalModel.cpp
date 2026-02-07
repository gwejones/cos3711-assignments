#include "JournalModel.h"
#include "JournalConstants.h"
#include "JournalValidation.h"
#include <QDate>

JournalModel::JournalModel(QObject *parent)
    : QStandardItemModel(parent)
{
}

bool JournalModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid()) {
        return false;
    }
    if (index.column() == JournalColumns::Year && (role == Qt::EditRole || role == Qt::DisplayRole)) {
        bool ok = false;
        const int year = value.toInt(&ok);
        if (!ok) {
            return false;
        }
        const int currentYear = QDate::currentDate().year();
        if (year > currentYear) {
            return false;
        }
        QStandardItem *item = itemFromIndex(index);
        if (item != nullptr) {
            item->setData(year, Qt::EditRole);
            item->setText(QString::number(year));
            // Force a full-row repain so age-based row coloring updates immediately.
            const int lastColumn = columnCount() > 0 ? columnCount() - 1 : 0;
            emit dataChanged(this->index(index.row(), 0),
                             this->index(index.row(), lastColumn),
                             {Qt::BackgroundRole, Qt::EditRole, Qt::DisplayRole});
            return true;
        }
    }
    if (role == Qt::EditRole || role == Qt::DisplayRole) {
        const QString text = value.toString().trimmed();
        switch (index.column()) {
        case JournalColumns::Author:
            if (!JournalValidation::isValidAuthor(text)) {
                return false;
            }
            return QStandardItemModel::setData(index, text, role);
        case JournalColumns::Title:
            if (!JournalValidation::isValidTitle(text)) {
                return false;
            }
            return QStandardItemModel::setData(index, text, role);
        case JournalColumns::Journal:
            if (!JournalValidation::isValidJournal(text)) {
                return false;
            }
            return QStandardItemModel::setData(index, text, role);
        case JournalColumns::Pages:
            if (!JournalValidation::isValidPages(text)) {
                return false;
            }
            return QStandardItemModel::setData(index, text, role);
        default:
            break;
        }
    }
    return QStandardItemModel::setData(index, value, role);
}
