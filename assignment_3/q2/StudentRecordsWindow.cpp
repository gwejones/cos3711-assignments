#include "StudentRecordsWindow.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QFormLayout>
#include <QLoggingCategory>
#include <QByteArray>
#include <QLineEdit>
#include <QProcess>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QVBoxLayout>

static constexpr int kWindowWidth = 420;
static constexpr int kWindowHeight = 200;
static constexpr const char *kGetStudentExecutableName = "q1";

StudentRecordsWindow::StudentRecordsWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Question 2");

    m_launchGetStudentButton = new QPushButton("Launch GetStudent");
    m_studentNumberLineEdit = new QLineEdit();
    m_moduleCodeLineEdit = new QLineEdit();
    m_markLineEdit = new QLineEdit();
    m_getStudentProcess = new QProcess(this);

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

    connect(m_launchGetStudentButton,
            &QPushButton::clicked,
            this,
            &StudentRecordsWindow::onLaunchGetStudentClicked);
    connect(m_getStudentProcess,
            &QProcess::readyReadStandardOutput,
            this,
            &StudentRecordsWindow::onGetStudentReadyReadStandardOutput);
    connect(m_getStudentProcess,
            &QProcess::readyReadStandardError,
            this,
            &StudentRecordsWindow::onGetStudentReadyReadStandardError);
    connect(m_getStudentProcess,
            &QProcess::errorOccurred,
            this,
            &StudentRecordsWindow::onGetStudentProcessErrorOccurred);
    connect(m_getStudentProcess,
            static_cast<void (QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
            this,
            &StudentRecordsWindow::onGetStudentProcessFinished);

    resize(kWindowWidth, kWindowHeight);
}

void StudentRecordsWindow::onLaunchGetStudentClicked()
{
    if (m_getStudentProcess->state() != QProcess::NotRunning) {
        return;
    }

    const QString executablePath = resolveGetStudentPath();
    if (!QFileInfo::exists(executablePath)) {
        qWarning() << "Could not resolve q1 executable path:" << executablePath;
        return;
    }

    m_standardOutputBuffer.clear();
    m_getStudentProcess->setProgram(executablePath);
    m_getStudentProcess->start();
}

void StudentRecordsWindow::onGetStudentReadyReadStandardOutput()
{
    const QByteArray outputChunk = m_getStudentProcess->readAllStandardOutput();
    m_standardOutputBuffer += QString::fromUtf8(outputChunk);

    int newlineIndex = m_standardOutputBuffer.indexOf('\n');
    while (newlineIndex >= 0) {
        QString line = m_standardOutputBuffer.left(newlineIndex);
        m_standardOutputBuffer.remove(0, newlineIndex + 1);

        // Remove trailing \r which might appear due to
        // Window's use of \r\n line endings.
        if (!line.isEmpty() && line.back() == '\r') {
            line.chop(1);
        }

        applyRecordFromOutputLine(line);
        newlineIndex = m_standardOutputBuffer.indexOf('\n');
    }
}

void StudentRecordsWindow::onGetStudentReadyReadStandardError()
{
    const QByteArray errorChunk = m_getStudentProcess->readAllStandardError();
    if (errorChunk.isEmpty()) {
        return;
    }

    qWarning() << "q1 stderr:" << QString::fromUtf8(errorChunk).trimmed();
}

void StudentRecordsWindow::onGetStudentProcessErrorOccurred(QProcess::ProcessError processError)
{
    qWarning() << "q1 process error:" << m_getStudentProcess->errorString();
    m_standardOutputBuffer.clear();
}

void StudentRecordsWindow::onGetStudentProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    // Clear any partial data so it is not mixed into output from the next q1 launch.
    m_standardOutputBuffer.clear();
}

void StudentRecordsWindow::applyRecordFromOutputLine(const QString &line)
{
    if (line.isEmpty()) {
        return;
    }

    const QStringList parts = line.split('|', Qt::KeepEmptyParts);
    if (parts.size() != 3) {
        qWarning() << "Ignoring malformed q1 output record:" << line;
        return;
    }

    const QString studentNumber = parts[0].trimmed();
    const QString moduleCode = parts[1].trimmed();
    const QString markText = parts[2].trimmed();
    if (studentNumber.isEmpty() || moduleCode.isEmpty()) {
        qWarning() << "Ignoring q1 output record with empty fields:" << line;
        return;
    }

    bool isMarkNumber = false;
    const int mark = markText.toInt(&isMarkNumber);
    if (!isMarkNumber) {
        qWarning() << "Ignoring q1 output record with non-numeric mark:" << line;
        return;
    }

    m_studentNumberLineEdit->setText(studentNumber);
    m_moduleCodeLineEdit->setText(moduleCode);
    m_markLineEdit->setText(QString::number(mark));
}

QString StudentRecordsWindow::resolveGetStudentPath() const
{
    const QString applicationDirectory = QCoreApplication::applicationDirPath();

#ifdef _WIN32
    const QString executableName = QString(kGetStudentExecutableName) + ".exe";
#else
    const QString executableName = QString(kGetStudentExecutableName);
#endif

    const QString candidateInAppDirectory = QDir(applicationDirectory).filePath(executableName);
    if (QFileInfo::exists(candidateInAppDirectory)) {
        return candidateInAppDirectory;
    }

    const QString candidateInParentDirectory =
        QDir(applicationDirectory).filePath("../" + executableName);
    return QDir::cleanPath(candidateInParentDirectory);
}
