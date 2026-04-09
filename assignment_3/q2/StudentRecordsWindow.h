#pragma once

#include <QWidget>

class QLineEdit;
class QPushButton;

class StudentRecordsWindow : public QWidget
{
public:
    explicit StudentRecordsWindow(QWidget *parent = nullptr);

private:
    QPushButton *m_launchGetStudentButton = nullptr;
    QLineEdit *m_studentNumberLineEdit = nullptr;
    QLineEdit *m_moduleCodeLineEdit = nullptr;
    QLineEdit *m_markLineEdit = nullptr;
};
