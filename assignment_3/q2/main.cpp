#include <QApplication>

#include "StudentRecordsWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    StudentRecordsWindow window;
    window.show();

    return app.exec();
}
