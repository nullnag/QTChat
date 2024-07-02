#include "mainwindow.h"
#include "loginreg.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginReg L;
    MainWindow main;
    L.show();
    return a.exec();
}
