#include <QCoreApplication>
#include <server.h>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;
    DBServer dbserver;
    return a.exec();
}
