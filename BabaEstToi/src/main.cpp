#include <QApplication>
#include "controller/guicontroller.h"
#include "view/mainwindow.h"


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    model::Baba model {};
    controller::GuiController controller {&model};
    view::MainWindow view {&model, &controller};

    view.show();
    return app.exec();
}
