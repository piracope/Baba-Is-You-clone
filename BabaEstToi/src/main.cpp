#include "controller/consolecontroller.h"
#include <QApplication>
#include "view/mainwindow.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}
