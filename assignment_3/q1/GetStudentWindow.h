#pragma once

#include <QWidget>

class QLineEdit;
class QPushButton;

class GetStudentWindow : public QWidget
{
public:
    explicit GetStudentWindow(QWidget *parent = nullptr);

private:
    QLineEdit *m_studentNumberLineEdit = nullptr;
    QLineEdit *m_moduleCodeLineEdit = nullptr;
    QLineEdit *m_markLineEdit = nullptr;
    QPushButton *m_addButton = nullptr;
};
