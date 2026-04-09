#include <QApplication>

#include "GetStudentWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    GetStudentWindow window;
    window.show();

    return app.exec();
}
