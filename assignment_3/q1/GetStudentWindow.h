#pragma once

#include <QWidget>

class QLineEdit;
class QPushButton;
class QString;

class GetStudentWindow : public QWidget
{
public:
    explicit GetStudentWindow(QWidget *parent = nullptr);

private:
    void onAddButtonClicked();
    bool validateInput(QString &errorMessage, QLineEdit *&errorField) const;
    void resetFormAfterSuccess();

    QLineEdit *m_studentNumberLineEdit = nullptr;
    QLineEdit *m_moduleCodeLineEdit = nullptr;
    QLineEdit *m_markLineEdit = nullptr;
    QPushButton *m_addButton = nullptr;
};
