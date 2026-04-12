#pragma once

#include <QProcess>
#include <QWidget>

class Student;
class QLineEdit;
class QPushButton;
class QString;
class QStandardItemModel;
class QTableView;

class StudentRecordsWindow : public QWidget
{
public:
    explicit StudentRecordsWindow(QWidget *parent = nullptr);

private:
    Student *findStudentFromLookupInput(QString &lookupNumber);

    void onLaunchGetStudentClicked();
    void onGetStudentReadyReadStandardOutput();
    void onGetStudentReadyReadStandardError();
    void onGetStudentProcessErrorOccurred(QProcess::ProcessError processError);
    void onGetStudentProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void applyRecordFromOutputLine(const QString &line);
    void onDisplayStudentRecordClicked();
    void onShowAverageClicked();
    void onCheckGraduationClicked();
    /**
     * Resolve the path to the Question 1 executable at runtime.
     * This is needed because q2 can be launched from different build layouts.
     * Hopefully this allows the solution to work in Windows, since
     * development and testing was done exclusively in a Linux environment.
     */
    QString resolveGetStudentPath() const;

    QString resolveStudentListXmlPath() const;

    QPushButton *m_launchGetStudentButton = nullptr;
    QLineEdit *m_studentNumberLineEdit = nullptr;
    QLineEdit *m_moduleCodeLineEdit = nullptr;
    QLineEdit *m_markLineEdit = nullptr;
    QLineEdit *m_lookupStudentNumberLineEdit = nullptr;
    QTableView *m_studentRecordTableView = nullptr;
    QLineEdit *m_averageLineEdit = nullptr;
    QLineEdit *m_graduationStatusLineEdit = nullptr;
    QPushButton *m_displayStudentRecordButton = nullptr;
    QPushButton *m_showAverageButton = nullptr;
    QPushButton *m_checkGraduationButton = nullptr;
    QStandardItemModel *m_studentRecordTableModel = nullptr;
    QProcess *m_getStudentProcess = nullptr;
    QString m_standardOutputBuffer;
};
