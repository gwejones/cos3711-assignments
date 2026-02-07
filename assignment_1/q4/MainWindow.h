#pragma once

#include <QMainWindow>

class JournalFilterProxy;
class JournalModel;
class QComboBox;
class QLineEdit;
class QSpinBox;
class QTableView;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// Main application window that owns the widgets and wires UI actions to the model.
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onAddClicked();
    void onApplyFilterClicked();
    void onClearFilterClicked();
    void onFilterFieldChanged(int index);
    void onRemoveClicked();

private:
    void setupUi();

    QLineEdit *m_authorEdit = nullptr;
    QLineEdit *m_titleEdit = nullptr;
    QLineEdit *m_journalEdit = nullptr;
    QLineEdit *m_pagesEdit = nullptr;
    QLineEdit *m_filterEdit = nullptr;
    QSpinBox *m_yearSpin = nullptr;
    QSpinBox *m_volumeSpin = nullptr;
    QSpinBox *m_issueSpin = nullptr;
    QTableView *m_tableView = nullptr;
    JournalModel *m_model = nullptr;
    JournalFilterProxy *m_proxy = nullptr;
    QComboBox *m_filterFieldCombo = nullptr;
    int m_currentYear = 0;
};
