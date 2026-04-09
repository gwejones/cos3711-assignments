#include "GetStudentWindow.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>

static constexpr int kWindowWidth = 420;
static constexpr int kWindowHeight = 200;
static constexpr int kStudentNumberLength = 4;
static constexpr int kModuleCodeLength = 7;
static constexpr int kMarkLength = 3;
static constexpr const char *kStudentNumberMask = "0000;_";   // Four required digits.
static constexpr const char *kModuleCodeMask = ">AAA000N;_";  // Uppercase 3 letters, 3 digits, 1 alphanumeric character.
static constexpr const char *kMarkMask = "099;_";             // One required digit, up to two optional digits.

GetStudentWindow::GetStudentWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("GetStudent - Question 1");

    m_studentNumberLineEdit = new QLineEdit();
    m_moduleCodeLineEdit = new QLineEdit();
    m_markLineEdit = new QLineEdit();
    m_addButton = new QPushButton("Add");

    m_studentNumberLineEdit->setInputMask(kStudentNumberMask);
    m_studentNumberLineEdit->setMaxLength(kStudentNumberLength);
    m_studentNumberLineEdit->setPlaceholderText("1234");

    m_moduleCodeLineEdit->setInputMask(kModuleCodeMask);
    m_moduleCodeLineEdit->setMaxLength(kModuleCodeLength);
    m_moduleCodeLineEdit->setPlaceholderText("COS3711");

    m_markLineEdit->setInputMask(kMarkMask);
    m_markLineEdit->setMaxLength(kMarkLength);
    m_markLineEdit->setPlaceholderText("000");

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
