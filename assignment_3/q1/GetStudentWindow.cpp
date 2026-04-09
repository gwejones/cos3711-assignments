#include "GetStudentWindow.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QRegularExpression>
#include <QString>
#include <QTextStream>
#include <QVBoxLayout>

static constexpr int kWindowWidth = 420;
static constexpr int kWindowHeight = 200;
static constexpr int kStudentNumberLength = 4;
static constexpr int kModuleCodeLength = 7;
static constexpr int kMarkLength = 3;
static constexpr const char *kStudentNumberMask = "0000";   // Four required digits.
static constexpr const char *kModuleCodeMask = ">AAA000N";  // Uppercase 3 letters, 3 digits, 1 alphanumeric character.
static constexpr const char *kMarkMask = "099";             // One required digit, up to two optional digits.
static constexpr const char *kStudentNumberPattern = "^\\d{4}$";
static constexpr const char *kModuleCodePattern = "^[A-Z]{3}[123]\\d{2}[A-Za-z0-9]$";
static constexpr const char *kMarkPattern = "^\\d{1,3}$";

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

    connect(m_addButton,
            &QPushButton::clicked,
            this,
            &GetStudentWindow::onAddButtonClicked);

    m_studentNumberLineEdit->setFocus();

    resize(kWindowWidth, kWindowHeight);
}

void GetStudentWindow::onAddButtonClicked()
{
    QString errorMessage;
    QLineEdit *errorField = nullptr;

    const bool isValid = validateInput(errorMessage, errorField);
    if (isValid) {
        const QString studentNumber = m_studentNumberLineEdit->text();
        const QString moduleCode = m_moduleCodeLineEdit->text();
        const int mark = m_markLineEdit->text().toInt();

        QTextStream output(stdout);
        output << studentNumber << "|" << moduleCode << "|" << mark << "\n";
        // Flush so that the process for Q2 can read immediately.
        output.flush();

        resetFormAfterSuccess();
        return;
    }

    QMessageBox::warning(this, "Invalid Input", errorMessage);
    if (errorField != nullptr) {
        errorField->setFocus();
        errorField->selectAll();
    }
}

bool GetStudentWindow::validateInput(QString &errorMessage, QLineEdit *&errorField) const
{
    const QString studentNumber = m_studentNumberLineEdit->text();
    const QRegularExpression studentNumberRegex(kStudentNumberPattern);
    const QRegularExpressionMatch studentNumberMatch = studentNumberRegex.match(studentNumber);
    if (!studentNumberMatch.hasMatch()) {
        errorMessage = "Student number must be exactly 4 digits.";
        errorField = m_studentNumberLineEdit;
        return false;
    }

    const QString moduleCode = m_moduleCodeLineEdit->text();
    const QRegularExpression moduleCodeRegex(kModuleCodePattern);
    const QRegularExpressionMatch moduleCodeMatch = moduleCodeRegex.match(moduleCode);
    if (!moduleCodeMatch.hasMatch()) {
        errorMessage = "Module code must be 3 uppercase letters, year digit (1, 2 or 3), 2 digits, and 1 alphanumeric character.";
        errorField = m_moduleCodeLineEdit;
        return false;
    }

    const QString markText = m_markLineEdit->text();
    const QRegularExpression markRegex(kMarkPattern);
    const QRegularExpressionMatch markMatch = markRegex.match(markText);
    if (!markMatch.hasMatch()) {
        errorMessage = "Mark must be a whole number between 0 and 100.";
        errorField = m_markLineEdit;
        return false;
    }

    bool isMarkNumber = false;
    const int mark = markText.toInt(&isMarkNumber);
    if (!isMarkNumber || mark < 0 || mark > 100) {
        errorMessage = "Mark must be an integer between 0 and 100.";
        errorField = m_markLineEdit;
        return false;
    }

    return true;
}

void GetStudentWindow::resetFormAfterSuccess()
{
    m_studentNumberLineEdit->clear();
    m_moduleCodeLineEdit->clear();
    m_markLineEdit->clear();
    m_studentNumberLineEdit->setFocus();
}
