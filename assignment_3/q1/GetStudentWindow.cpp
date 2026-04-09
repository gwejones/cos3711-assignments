#include "GetStudentWindow.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

namespace
{
constexpr int kWindowWidth = 420;
constexpr int kWindowHeight = 200;
}

GetStudentWindow::GetStudentWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("GetStudent - Question 1");

    m_studentNumberLineEdit = new QLineEdit();
    m_moduleCodeLineEdit = new QLineEdit();
    m_markLineEdit = new QLineEdit();
    m_addButton = new QPushButton("Add");

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Student Number", m_studentNumberLineEdit);
    formLayout->addRow("Module Code", m_moduleCodeLineEdit);
    formLayout->addRow("Mark", m_markLineEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(m_addButton);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(10);

    resize(kWindowWidth, kWindowHeight);
}
