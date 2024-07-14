#ifndef SERVER_H
#define SERVER_H
#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>
#include <QSqlDatabase>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDateTime>
#include <QSqlQuery>
#include <QMap>
#include <QSet>

struct Message {
    QString sender;
    QString receiver;
    QString content;
};

class Server : public QTcpServer{
    Q_OBJECT;
public:
    Server();
    ~Server();
    QTcpSocket* socket;
private:
    QList<Message> messages;
    QByteArray Data;
    QString Login;
    QMap<QTcpSocket*,QString> Sockets;
    void SendToClient(QString str, QVector<QTcpSocket*> messagingUsers);
    quint16 nextBlockSize;
    QSet<QString> AllowUsers;

public slots:
    void SaveMessages();
    void loadMessages();
    void incomingConnection(qintptr socketDescriptor);
    void UpdateMessages(QTcpSocket* senderSock, QString sender, QString reciever);
    virtual void sockReady();
    virtual void sockDisc();
    void SendAllowClients(QMap<QTcpSocket*,QString> Sockets);
};



class DBServer : public Server{
    Q_OBJECT;
public:
    DBServer();
    ~DBServer();
    QTcpSocket* clientSocket;
    QSet<QTcpSocket*>* clientSockets;
private:

    QSqlDatabase db;
    QMap <qintptr, QTcpSocket*> clients;
    QSqlQuery* query;
    QByteArray Data;
    void SendToClient(bool check,qint32 requestNum, QTcpSocket* clientSocket);
    quint16 nextBlockSize;


public slots:
    void incomingConnection(qintptr socketDescriptor) override;
    void sockReady() override;
    void sockDisc() override;
};
#endif // SERVER_H
