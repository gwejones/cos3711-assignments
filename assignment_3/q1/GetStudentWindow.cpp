#include "GetStudentWindow.h"

namespace
{
constexpr int kWindowWidth = 420;
constexpr int kWindowHeight = 180;
}

GetStudentWindow::GetStudentWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("GetStudent - Question 1");
    resize(kWindowWidth, kWindowHeight);
}
