#include "mainwindow.h"
#include "loginreg.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    LoginReg L;
    //w.show();
    L.show();
    return a.exec();
}
