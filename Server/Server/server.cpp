#include <server.h>

DBServer::DBServer(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/boiko/Desktop/d/users.db");
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
    connect(socket,&QTcpSocket::readyRead,this, &DBServer::sockReady);
    connect(socket,&QTcpSocket::disconnected,this,&DBServer::sockDisc);
    qDebug() << socketDescriptor << " connected 2";
    qDebug() << socket;
}
void DBServer::sockDisc(){
    qDebug() << "disc 2" << socket;
    QTcpSocket* disconnectedSocket = qobject_cast<QTcpSocket*>(sender());
    disconnectedSocket->deleteLater();
}
void DBServer::sockReady(){

    Data.clear();
    QString username, password;
    Data = socket->readAll();
    QDataStream stream(&Data, QIODevice::ReadOnly);
    qint32 requestNum;
    stream >> requestNum >> username >> password;
    qDebug() << requestNum;
    switch (requestNum){
        case 1:
            qDebug() << username;
            qDebug() << password;
            this->query->prepare("SELECT COUNT(*) FROM users WHERE username = :username AND password = :password");
            this->query->bindValue(":username", username);
            this->query->bindValue(":password",password);
            if (!query->exec()){
                qDebug() << "Ошибка выполнения запроса";
            }
            if (this->query->next()){
                int count = this->query->value(0).toInt();
                DBServer::SendToClient(count > 0,1);
                qDebug() << count;
            }
            break;

        case 2:

            this->query->prepare("INSERT INTO users (username,password) VALUES(:username, :password)");
            this->query->bindValue(":username",username);
            this->query->bindValue(":password",password);
            if (!this->query->exec()) {
                qDebug() << "Ошибка выполнения запроса:";
            } else {
                qDebug() << "Данные успешно записаны в базу данных";
            }
            break;
        case 3:
            qDebug() << username;
            this->query->prepare("SELECT COUNT(*) FROM users WHERE username = :username");
            this->query->bindValue(":username",username);
            if (!query->exec()) {
                qDebug() << "Ошибка при выполнении запроса:";
            }
            if (this->query->next()){
                int count = this->query->value(0).toInt();
                DBServer::SendToClient(count > 0,3);
                qDebug() << count;
            }

            break;
        default:
            break;
    };

}

void DBServer::SendToClient(bool check,qint32 requestNum){
    Data.clear();
    qDebug() << requestNum;
    QDataStream stream(&Data, QIODevice::WriteOnly);
    stream << check << requestNum;
    socket->write(Data);
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
