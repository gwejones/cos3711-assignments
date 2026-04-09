#pragma once

#include <QWidget>

class QLineEdit;
class QProcess;
class QPushButton;
class QString;

class StudentRecordsWindow : public QWidget
{
public:
    explicit StudentRecordsWindow(QWidget *parent = nullptr);

private:
    void onLaunchGetStudentClicked();
    void onGetStudentReadyReadStandardOutput();
    void applyRecordFromOutputLine(const QString &line);
    /**
     * Resolve the path to the Question 1 executable at runtime.
     * This is needed because q2 can be launched from different build layouts.
     * Hopefully this allows the solution to work in Windows, since
     * development and testing was done exclusively in a Linux environment.
     */
    QString resolveGetStudentPath() const;

    QPushButton *m_launchGetStudentButton = nullptr;
    QLineEdit *m_studentNumberLineEdit = nullptr;
    QLineEdit *m_moduleCodeLineEdit = nullptr;
    QLineEdit *m_markLineEdit = nullptr;
    QProcess *m_getStudentProcess = nullptr;
    QString m_standardOutputBuffer;
};
