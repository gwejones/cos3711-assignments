#include <QApplication>

#include "ShapesWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ShapesWindow window;
    window.show();

    return app.exec();
}
