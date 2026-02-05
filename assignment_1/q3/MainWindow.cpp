#include "MainWindow.h"
#include "JournalConstants.h"
#include "JournalFilterProxy.h"
#include "JournalModel.h"
#include "SpinBoxDelegate.h"
#include <QAbstractItemView>
#include <QComboBox>
#include <QDate>
#include <QFormLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QSpinBox>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTableView>
#include <QVBoxLayout>
#include <algorithm>
#include <vector>

static QStandardItem *makeTextItem(const QString &text)
{
    QStandardItem *item = new QStandardItem(text);
    item->setData(text, Qt::EditRole);
    return item;
}

static QStandardItem *makeNumberItem(int value)
{
    QStandardItem *item = new QStandardItem(QString::number(value));
    item->setData(value, Qt::EditRole);
    item->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
    return item;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
}

void MainWindow::setupUi()
{
    setWindowTitle(QStringLiteral("Journals"));
    setMinimumSize(960, 540);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QHBoxLayout *outerLayout = new QHBoxLayout(central);
    QSplitter *splitter = new QSplitter(Qt::Horizontal, central);
    outerLayout->addWidget(splitter);

    QWidget *leftPane = new QWidget(splitter);
    QWidget *rightPane = new QWidget(splitter);
    splitter->addWidget(leftPane);
    splitter->addWidget(rightPane);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    splitter->setSizes({3, 7});

    QVBoxLayout *leftLayout = new QVBoxLayout(leftPane);
    leftLayout->setContentsMargins(0, 0, 0, 0);

    m_currentYear = QDate::currentDate().year();

    QGroupBox *detailsGroup = new QGroupBox(QStringLiteral("Article Details"), leftPane);
    QFormLayout *detailsLayout = new QFormLayout(detailsGroup);

    QLineEdit *authorEdit = new QLineEdit(detailsGroup);
    QLineEdit *titleEdit = new QLineEdit(detailsGroup);
    QLineEdit *journalEdit = new QLineEdit(detailsGroup);
    QLineEdit *pagesEdit = new QLineEdit(detailsGroup);
    pagesEdit->setPlaceholderText(QStringLiteral("e.g. 12-14"));

    QSpinBox *yearSpin = new QSpinBox(detailsGroup);
    yearSpin->setRange(1, m_currentYear);
    yearSpin->setValue(m_currentYear);

    QSpinBox *volumeSpin = new QSpinBox(detailsGroup);
    volumeSpin->setRange(1, 10000);
    volumeSpin->setValue(1);

    QSpinBox *issueSpin = new QSpinBox(detailsGroup);
    issueSpin->setRange(1, 10000);
    issueSpin->setValue(1);

    // Keep widget pointers so slot handlers can access current UI state.
    m_authorEdit = authorEdit;
    m_titleEdit = titleEdit;
    m_journalEdit = journalEdit;
    m_pagesEdit = pagesEdit;
    m_yearSpin = yearSpin;
    m_volumeSpin = volumeSpin;
    m_issueSpin = issueSpin;

    detailsLayout->addRow(QStringLiteral("Author"), authorEdit);
    detailsLayout->addRow(QStringLiteral("Year"), yearSpin);
    detailsLayout->addRow(QStringLiteral("Title"), titleEdit);
    detailsLayout->addRow(QStringLiteral("Journal"), journalEdit);
    detailsLayout->addRow(QStringLiteral("Volume"), volumeSpin);
    detailsLayout->addRow(QStringLiteral("Issue"), issueSpin);
    detailsLayout->addRow(QStringLiteral("Pages"), pagesEdit);

    leftLayout->addWidget(detailsGroup);

    QHBoxLayout *buttonRow = new QHBoxLayout;
    QPushButton *addButton = new QPushButton(QStringLiteral("Add"), detailsGroup);
    QPushButton *removeButton = new QPushButton(QStringLiteral("Remove"), detailsGroup);
    buttonRow->addWidget(addButton);
    buttonRow->addWidget(removeButton);
    detailsLayout->addRow(buttonRow);

    QGroupBox *filterGroup = new QGroupBox(QStringLiteral("Filter"), leftPane);
    QFormLayout *filterLayout = new QFormLayout(filterGroup);

    QComboBox *filterFieldCombo = new QComboBox(filterGroup);
    m_filterFieldCombo = filterFieldCombo;
    filterFieldCombo->addItem(QStringLiteral("Author"), JournalColumns::Author);
    filterFieldCombo->addItem(QStringLiteral("Year"), JournalColumns::Year);
    filterFieldCombo->addItem(QStringLiteral("Title"), JournalColumns::Title);
    filterFieldCombo->addItem(QStringLiteral("Journal"), JournalColumns::Journal);
    filterFieldCombo->addItem(QStringLiteral("Volume"), JournalColumns::Volume);
    filterFieldCombo->addItem(QStringLiteral("Issue"), JournalColumns::Issue);

    QLineEdit *filterEdit = new QLineEdit(filterGroup);
    filterEdit->setPlaceholderText(QStringLiteral("e.g. *jones*"));
    filterEdit->setClearButtonEnabled(true);
    // Storedd for filter actions triggered by buttons and combo changes.
    m_filterEdit = filterEdit;

    QHBoxLayout *filterButtons = new QHBoxLayout;
    QPushButton *applyFilterButton = new QPushButton(QStringLiteral("Apply"), filterGroup);
    QPushButton *clearFilterButton = new QPushButton(QStringLiteral("Clear"), filterGroup);
    filterButtons->addWidget(applyFilterButton);
    filterButtons->addWidget(clearFilterButton);

    filterLayout->addRow(QStringLiteral("Field"), filterFieldCombo);
    filterLayout->addRow(QStringLiteral("Pattern"), filterEdit);
    filterLayout->addRow(filterButtons);

    leftLayout->addWidget(filterGroup);
    leftLayout->addStretch(1);

    QVBoxLayout *rightLayout = new QVBoxLayout(rightPane);
    rightLayout->setContentsMargins(0, 0, 0, 0);

    QTableView *tableView = new QTableView(rightPane);
    m_tableView = tableView;
    rightLayout->addWidget(tableView);

    JournalModel *model = new JournalModel(this);
    m_model = model;
    model->setColumnCount(JournalColumns::ColumnCount);
    model->setHorizontalHeaderLabels(
        {QStringLiteral("Author"), QStringLiteral("Year"), QStringLiteral("Title"),
         QStringLiteral("Journal"), QStringLiteral("Volume"), QStringLiteral("Issue"),
         QStringLiteral("Pages")});

    JournalFilterProxy *proxy = new JournalFilterProxy(this);
    m_proxy = proxy;
    proxy->setSourceModel(model);
    proxy->setSortRole(Qt::EditRole);
    proxy->setDynamicSortFilter(true);

    tableView->setModel(proxy);
    tableView->setSortingEnabled(true);
    tableView->sortByColumn(JournalColumns::Author, Qt::AscendingOrder);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tableView->setAlternatingRowColors(true);
    tableView->setEditTriggers(QAbstractItemView::DoubleClicked
                               | QAbstractItemView::SelectedClicked
                               | QAbstractItemView::EditKeyPressed);
    tableView->horizontalHeader()->setStretchLastSection(true);

    tableView->setItemDelegateForColumn(
        JournalColumns::Year, new SpinBoxDelegate(1, m_currentYear, tableView));
    tableView->setItemDelegateForColumn(
        JournalColumns::Volume, new SpinBoxDelegate(1, 10000, tableView));
    tableView->setItemDelegateForColumn(
        JournalColumns::Issue, new SpinBoxDelegate(1, 10000, tableView));

    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddClicked);
    connect(removeButton, &QPushButton::clicked, this, &MainWindow::onRemoveClicked);
    connect(applyFilterButton, &QPushButton::clicked, this, &MainWindow::onApplyFilterClicked);
    connect(filterEdit, &QLineEdit::returnPressed, applyFilterButton, &QPushButton::click);
    connect(clearFilterButton, &QPushButton::clicked, this, &MainWindow::onClearFilterClicked);
    connect(filterFieldCombo, qOverload<int>(&QComboBox::currentIndexChanged), this,
            &MainWindow::onFilterFieldChanged);
}

void MainWindow::onFilterFieldChanged(int index)
{
    (void)index;
    if (m_proxy == nullptr || m_filterFieldCombo == nullptr) {
        return;
    }
    m_proxy->setFilterField(m_filterFieldCombo->currentData().toInt());
}

void MainWindow::onAddClicked()
{
    if (m_model == nullptr || m_tableView == nullptr || m_authorEdit == nullptr
        || m_titleEdit == nullptr || m_journalEdit == nullptr || m_pagesEdit == nullptr
        || m_yearSpin == nullptr || m_volumeSpin == nullptr || m_issueSpin == nullptr) {
        return;
    }

    const QString author = m_authorEdit->text().trimmed();
    const QString title = m_titleEdit->text().trimmed();
    const QString journal = m_journalEdit->text().trimmed();
    const QString pages = m_pagesEdit->text().trimmed();

    QList<QStandardItem *> row;
    row << makeTextItem(author)
        << makeNumberItem(m_yearSpin->value())
        << makeTextItem(title)
        << makeTextItem(journal)
        << makeNumberItem(m_volumeSpin->value())
        << makeNumberItem(m_issueSpin->value())
        << makeTextItem(pages);

    m_model->appendRow(row);
    m_tableView->scrollToBottom();

    m_authorEdit->clear();
    m_titleEdit->clear();
    m_journalEdit->clear();
    m_pagesEdit->clear();
    m_yearSpin->setValue(m_currentYear);
    m_volumeSpin->setValue(1);
    m_issueSpin->setValue(1);
    m_authorEdit->setFocus();
}

void MainWindow::onApplyFilterClicked()
{
    if (m_proxy == nullptr || m_filterFieldCombo == nullptr || m_filterEdit == nullptr) {
        return;
    }
    // Proxy filter uses the selected field and wildcard pattern to filter rows.
    m_proxy->setFilterField(m_filterFieldCombo->currentData().toInt());
    m_proxy->setWildcardFilter(m_filterEdit->text().trimmed());
}

void MainWindow::onClearFilterClicked()
{
    if (m_proxy == nullptr || m_filterEdit == nullptr) {
        return;
    }
    m_filterEdit->clear();
    m_proxy->setWildcardFilter(QString());
}

void MainWindow::onRemoveClicked()
{
    if (m_model == nullptr || m_proxy == nullptr || m_tableView == nullptr) {
        return;
    }
    const QModelIndexList selection = m_tableView->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        return;
    }
    // Remove in descending order so row indices stay valid as rows are deleted.
    std::vector<int> rows;
    rows.reserve(selection.size());
    for (const QModelIndex &proxyIndex : selection) {
        rows.push_back(m_proxy->mapToSource(proxyIndex).row());
    }
    std::sort(rows.begin(), rows.end(), std::greater<int>());
    for (int row : rows) {
        m_model->removeRow(row);
    }
}
