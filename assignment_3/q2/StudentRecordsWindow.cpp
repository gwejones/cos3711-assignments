#include "StudentRecordsWindow.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

static constexpr int kWindowWidth = 420;
static constexpr int kWindowHeight = 200;

StudentRecordsWindow::StudentRecordsWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Question 2");

    m_launchGetStudentButton = new QPushButton("Launch GetStudent");
    m_studentNumberLineEdit = new QLineEdit();
    m_moduleCodeLineEdit = new QLineEdit();
    m_markLineEdit = new QLineEdit();

    m_studentNumberLineEdit->setReadOnly(true);
    m_moduleCodeLineEdit->setReadOnly(true);
    m_markLineEdit->setReadOnly(true);

    m_studentNumberLineEdit->setPlaceholderText("Student number");
    m_moduleCodeLineEdit->setPlaceholderText("Module code");
    m_markLineEdit->setPlaceholderText("Mark");

    QFormLayout *displayLayout = new QFormLayout();
    displayLayout->addRow("Student Number", m_studentNumberLineEdit);
    displayLayout->addRow("Module Code", m_moduleCodeLineEdit);
    displayLayout->addRow("Mark", m_markLineEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(displayLayout);
    mainLayout->addWidget(m_launchGetStudentButton);
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(10);

    resize(kWindowWidth, kWindowHeight);
}
