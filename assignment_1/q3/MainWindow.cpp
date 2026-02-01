#include "MainWindow.h"
#include <QLabel>
#include <QtCore/Qt>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(QStringLiteral("q3 - Qt6 GUI Stub"));
    setMinimumSize(640, 360);
}
