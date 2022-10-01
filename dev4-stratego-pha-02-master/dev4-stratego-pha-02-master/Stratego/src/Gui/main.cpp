#include "mainwindow.h"
#include "controllergui.h"
#include "leftWidget.h"

#include <QApplication>

int main(int argc, char * argv[])
{
    QApplication a(argc, argv);

    ControllerGui controller;
    MainWindow w(nullptr, &controller);
    controller.addObserver(&w);
    w.show();
    return a.exec();
}
