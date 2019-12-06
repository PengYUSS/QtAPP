#include "mainwindow.h"
#include "movement.h"


#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    movement m;

    return a.exec();
}
