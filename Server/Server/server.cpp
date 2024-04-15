#include <server.h>

DBServer::DBServer(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/qt/SQLCHAT/users.db");
    if (db.open()){
        qDebug() << "open database";
    }
    else{
        qDebug() << "failt to open";
    }
    query = new QSqlQuery(db);
    query->exec("CREATE TABLE users(id INT AUTO_INCREMENT PRIMARY KEY,"
                "username VARCHAR(255) UNIQUE NOT NULL,"
                "password VARCHAR(255) NOT NULL)");
    if (this->listen(QHostAddress::Any, 4444)){
        qDebug() << "listen 4444";
    }
    else{
        qDebug() << "error";
    }
    nextBlockSize = 0;
}
void DBServer::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket,&QTcpSocket::readyRead,this, &Server::sockReady);
    connect(socket,&QTcpSocket::disconnected,this,&Server::sockDisc);
    qDebug() << socketDescriptor << " connected 2";
}
void DBServer::sockReady(){

    this->Data = socket->readAll();
    QList<QByteArray> parts = Data.split(':');
    QString login = parts[0];
    QString password = parts[1];
    this->query->prepare("INSERT INTO users (username,password) VALUES(:username, :password)");
    this->query->bindValue(":username",login);
    this->query->bindValue(":password",password);
    if (!this->query->exec()) {
        qDebug() << "Ошибка выполнения запроса:";
    } else {
        qDebug() << "Данные успешно записаны в базу данных";
    }
}
void DBServer::sockDisc(){
    qDebug() << "disc 2";
    socket->deleteLater();
}

Server::Server(){
    if (this->listen(QHostAddress::Any, 5555)){
        qDebug() << "listen 5555";
    }
    else{
        qDebug() << "error";
    }
    nextBlockSize = 0;
}
void Server::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket,&QTcpSocket::readyRead,this, &Server::sockReady);
    connect(socket,&QTcpSocket::disconnected,this,&Server::sockDisc);
    Sockets.push_back(socket);
    qDebug() << Sockets.size();
    qDebug() << socketDescriptor << " connected";
}
void Server::sockReady(){
        socket = (QTcpSocket*)sender();
        QDataStream in(socket);
        in.setVersion(QDataStream::Version());
        if(in.status() == QDataStream::Ok ){
            for (;;){
                if (nextBlockSize == 0){
                    if (socket->bytesAvailable() < 2){
                        break;
                    }
                    in >> nextBlockSize;
                }
                if (socket->bytesAvailable() < nextBlockSize){
                    break;
                }
                QString str;
                in >> str;
                nextBlockSize = 0;
                SendToClient(str);
                break;
            }
        }
        else{
            qDebug() << "error";
        }
}
void Server::sockDisc(){
    qDebug() << "disc";
    QTcpSocket* disconnectedSocket = qobject_cast<QTcpSocket*>(sender());
    Sockets.removeOne(disconnectedSocket);
    disconnectedSocket->deleteLater();
}

void Server::SendToClient(QString str){
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Version());
    out << quint16(0) << str;
    out.device()->seek(0);
    out << quint16(Data.size() - sizeof(quint16));
    for (int i = 0; i < Sockets.size(); i++){
        Sockets[i]->write(Data);
    }
}
