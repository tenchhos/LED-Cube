#include <QApplication>
#include <QtWidgets>
#include <QLabel>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;
    window.setMaximumWidth(540);        //set maxWidth same as default
    window.setMaximumHeight(340);       //set maxHeight same as default
    window.show();
    return app.exec();
}
