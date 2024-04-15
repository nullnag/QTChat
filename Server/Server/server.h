#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QSqlDatabase>
#include <QSqlQuery>




class Server : public QTcpServer{
    Q_OBJECT;
public:
    Server();
    QTcpSocket* socket;
private:
    QByteArray Data;
    QVector<QTcpSocket*> Sockets;
    void SendToClient(QString str);
    quint16 nextBlockSize;

public slots:
    void incomingConnection(qintptr socketDescriptor);
    virtual void sockReady();
    virtual void sockDisc();
};
class DBServer : public Server{
    Q_OBJECT;
public:
    DBServer();
    QTcpSocket* socket;
private:
    QSqlDatabase db;
    QSqlQuery* query;
    QByteArray Data;
    void SendToClient(QString str);
    quint16 nextBlockSize;


public slots:
    void incomingConnection(qintptr socketDescriptor) override;
    void sockReady() override;
    void sockDisc() override;
};
#endif // SERVER_H
