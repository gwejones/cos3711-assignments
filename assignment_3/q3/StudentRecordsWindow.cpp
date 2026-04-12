#include "StudentRecordsWindow.h"

#include "Student.h"
#include "StudentList.h"

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLoggingCategory>
#include <QByteArray>
#include <QLineEdit>
#include <QProcess>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QVBoxLayout>

static constexpr int kWindowWidth = 420;
static constexpr int kWindowHeight = 340;
static constexpr const char *kGetStudentExecutableName = "q1";

StudentRecordsWindow::StudentRecordsWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Question 3");

    m_launchGetStudentButton = new QPushButton("Launch GetStudent");
    m_displayStudentRecordButton = new QPushButton("Display Student Record");
    m_showAverageButton = new QPushButton("Show Average");
    m_checkGraduationButton = new QPushButton("Check Graduation");
    m_studentNumberLineEdit = new QLineEdit();
    m_moduleCodeLineEdit = new QLineEdit();
    m_markLineEdit = new QLineEdit();
    m_lookupStudentNumberLineEdit = new QLineEdit();
    m_studentRecordLineEdit = new QLineEdit();
    m_averageLineEdit = new QLineEdit();
    m_graduationStatusLineEdit = new QLineEdit();
    m_getStudentProcess = new QProcess(this);

    m_studentNumberLineEdit->setReadOnly(true);
    m_moduleCodeLineEdit->setReadOnly(true);
    m_markLineEdit->setReadOnly(true);
    m_studentRecordLineEdit->setReadOnly(true);
    m_averageLineEdit->setReadOnly(true);
    m_graduationStatusLineEdit->setReadOnly(true);

    m_studentNumberLineEdit->setPlaceholderText("Latest student number");
    m_moduleCodeLineEdit->setPlaceholderText("Latest module code");
    m_markLineEdit->setPlaceholderText("Latest mark");
    m_lookupStudentNumberLineEdit->setPlaceholderText("Enter student number");
    m_studentRecordLineEdit->setPlaceholderText("Student modules and marks");
    m_averageLineEdit->setPlaceholderText("Average mark");
    m_graduationStatusLineEdit->setPlaceholderText("Graduation status");

    QFormLayout *latestRecordLayout = new QFormLayout();
    latestRecordLayout->addRow("Latest Student Number", m_studentNumberLineEdit);
    latestRecordLayout->addRow("Latest Module Code", m_moduleCodeLineEdit);
    latestRecordLayout->addRow("Latest Mark", m_markLineEdit);

    QHBoxLayout *queryActionsLayout = new QHBoxLayout();
    queryActionsLayout->addWidget(m_displayStudentRecordButton);
    queryActionsLayout->addWidget(m_showAverageButton);
    queryActionsLayout->addWidget(m_checkGraduationButton);

    QFormLayout *queryResultsLayout = new QFormLayout();
    queryResultsLayout->addRow("Lookup Student Number", m_lookupStudentNumberLineEdit);
    queryResultsLayout->addRow(queryActionsLayout);
    queryResultsLayout->addRow("Student Record", m_studentRecordLineEdit);
    queryResultsLayout->addRow("Average", m_averageLineEdit);
    queryResultsLayout->addRow("Graduation", m_graduationStatusLineEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(queryResultsLayout);
    mainLayout->addLayout(latestRecordLayout);
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
    connect(m_displayStudentRecordButton,
            &QPushButton::clicked,
            this,
            &StudentRecordsWindow::onDisplayStudentRecordClicked);
    connect(m_showAverageButton,
            &QPushButton::clicked,
            this,
            &StudentRecordsWindow::onShowAverageClicked);
    connect(m_checkGraduationButton,
            &QPushButton::clicked,
            this,
            &StudentRecordsWindow::onCheckGraduationClicked);

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

Student *StudentRecordsWindow::findStudentFromLookupInput(QString &lookupNumber) const
{
    lookupNumber = m_lookupStudentNumberLineEdit->text().trimmed();
    if (lookupNumber.isEmpty()) {
        qWarning() << "Lookup student number is empty.";
        return nullptr;
    }

    StudentList &studentList = StudentList::instance();
    const int studentIndex = studentList.indexOfStudentNumber(lookupNumber);
    if (studentIndex < 0) {
        qWarning() << "Could not find student number:" << lookupNumber;
        return nullptr;
    }

    Student *student = studentList.getStudent(studentIndex);
    if (student == nullptr) {
        qWarning() << "Student list returned null pointer for existing index:" << studentIndex;
        return nullptr;
    }

    return student;
}

void StudentRecordsWindow::onDisplayStudentRecordClicked()
{
    QString lookupNumber;
    Student *student = findStudentFromLookupInput(lookupNumber);
    if (student == nullptr) {
        m_studentRecordLineEdit->clear();
        return;
    }

    const Student::ModulesContainer &modules = student->getModules();
    if (modules.isEmpty()) {
        m_studentRecordLineEdit->setText("No modules.");
        return;
    }

    QStringList recordParts;
    for (Student::ModulesContainer::const_iterator it = modules.cbegin();
         it != modules.cend();
         ++it) {
        recordParts.append(it.key() + ":" + QString::number(it.value()));
    }

    m_studentRecordLineEdit->setText(recordParts.join(", "));
}

void StudentRecordsWindow::onShowAverageClicked()
{
    QString lookupNumber;
    Student *student = findStudentFromLookupInput(lookupNumber);
    if (student == nullptr) {
        m_averageLineEdit->clear();
        return;
    }

    m_averageLineEdit->setText(QString::number(student->average(), 'f', 2));
}

void StudentRecordsWindow::onCheckGraduationClicked()
{
    QString lookupNumber;
    Student *student = findStudentFromLookupInput(lookupNumber);
    if (student == nullptr) {
        m_graduationStatusLineEdit->clear();
        return;
    }

    const bool qualifies = student->graduate();
    m_graduationStatusLineEdit->setText(qualifies ? "Qualifies" : "Does not qualify");
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

    StudentList &studentList = StudentList::instance();
    const int studentIndex = studentList.indexOfStudentNumber(studentNumber);

    Student *student = nullptr;
    if (studentIndex < 0) {
        student = new Student();
        student->setNumber(studentNumber);
        studentList.addStudent(student);
    } else {
        student = studentList.getStudent(studentIndex);
        if (student == nullptr) {
            qWarning() << "Student list returnd null pointer for existing index:" << studentIndex;
            return;
        }
    }

    student->addModule(moduleCode, mark);

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
