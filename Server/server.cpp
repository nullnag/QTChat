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
        qDebug() << "error 4444";
    }
    clientSockets = new QSet<QTcpSocket*>();
}


void DBServer::incomingConnection(qintptr socketDescriptor){
    clientSocket = new QTcpSocket(this);
    clientSocket->setSocketDescriptor(socketDescriptor);
    connect(clientSocket,&QTcpSocket::readyRead,this, &DBServer::sockReady);
    connect(clientSocket,&QTcpSocket::disconnected,this,&DBServer::sockDisc);
    clientSockets->insert(clientSocket);
    qDebug() << socketDescriptor << " connected 2";
    qDebug() << this->clientSocket;
}
void DBServer::sockDisc(){
    QTcpSocket* disconnectedSocketDB = qobject_cast<QTcpSocket*>(sender());
    if (disconnectedSocketDB) {
        qDebug() << "Disconnected socket:" << disconnectedSocketDB;
        clientSockets->remove(disconnectedSocketDB);
        disconnectedSocketDB->deleteLater();
    } else {
        qDebug() << "Error: Sender is not a QTcpSocket.";
    }
}
void DBServer::sockReady(){
    QTcpSocket* clientSocket = qobject_cast<QTcpSocket*>(sender());
    if (!clientSocket) return;
    Data.clear();
    QString username, password;
    Data = clientSocket->readAll();
    QDataStream stream(&Data, QIODevice::ReadOnly);
    qint32 requestNum = 0;
    stream >> requestNum >> username >> password;
    qDebug() << requestNum << " RequestID";
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
                DBServer::SendToClient(count > 0,1,clientSocket);
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
                DBServer::SendToClient(count > 0,3,clientSocket);
                qDebug() << count;
            }

            break;
        default:
            break;
    };

}

void DBServer::SendToClient(bool check,qint32 requestNum, QTcpSocket* clientSocket){
    Data.clear();
    QDataStream stream(&Data, QIODevice::WriteOnly);
    stream << check << requestNum;
    clientSocket->write(Data);
}

Server::Server(){

    if (this->listen(QHostAddress::Any, 5555)){
        qDebug() << "listen 5555";
    }
    else{
        qDebug() << "error 5555";
    }
    loadMessages();
}
void Server::incomingConnection(qintptr socketDescriptor){
    socket = new QTcpSocket;
    socket->setSocketDescriptor(socketDescriptor);
    connect(socket,&QTcpSocket::readyRead,this, &Server::sockReady);
    connect(socket,&QTcpSocket::disconnected,this,&Server::sockDisc);
    Sockets.insert(socket,Login);
    qDebug() << Sockets.size();
    qDebug() << socketDescriptor << " connected";
}

void Server::sockReady(){
    QTcpSocket* socket = (QTcpSocket*)sender();
    if (!socket) return;
    QString sender;
    qint32 requestNum = 0;
    QVector<QTcpSocket*> messagingUsers = {};
    QDataStream in(socket);
    in.setVersion(QDataStream::Version());
    QString str = "";
    QString ChosenUser = "";
    in >> requestNum >> str >> ChosenUser;
    qDebug() << requestNum << "Текущий процесс";
    switch (requestNum) {
    case 3:
        UpdateMessages(socket, str, ChosenUser);
        break;
    case 1:
        Sockets[socket] = str;
        for (auto it = Sockets.constBegin(); it != Sockets.constEnd(); ++it) {
            this->AllowUsers.insert(it.value());
        }
        SendAllowClients(Sockets);
        break;
    case 2:
        for (auto it = Sockets.constBegin(); it != Sockets.constEnd(); ++it) {
            if (it.value() == ChosenUser){
                messagingUsers.append(it.key());
                messagingUsers.append(socket);
            }
            if (it.key() == socket){
                sender = it.value();
            }
        }
        Message message;
        message.content = str;
        message.receiver = ChosenUser;
        message.sender = sender;
        messages.append(message);
        SaveMessages();
        SendToClient(str, messagingUsers);
        break;
        };


}

void Server::SaveMessages(){
    QFile file("C:/Program Files (x86)/qt/SQLCHAT/Client/Server/Server/saver.json");
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Could not open file for writing.");
        return;
    }
    QJsonArray jsonMessages;
    for (const auto &message : messages) {
        QJsonObject jsonMessage;
        jsonMessage["sender"] = message.sender;
        jsonMessage["receiver"] = message.receiver;
        jsonMessage["content"] = message.content;
        jsonMessages.append(jsonMessage);
    }

    QJsonDocument doc(jsonMessages);
    file.write(doc.toJson());
}
void Server::loadMessages(){
    QFile file("C:/Program Files (x86)/qt/SQLCHAT/Client/Server/Server/saver.json");
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Could not open file for reading.");
        return;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonArray jsonMessages = doc.array();
    for (const auto &jsonValue : jsonMessages) {
        QJsonObject jsonMessage = jsonValue.toObject();
        Message message;
        message.sender = jsonMessage["sender"].toString();
        message.receiver = jsonMessage["receiver"].toString();
        message.content = jsonMessage["content"].toString();
        messages.append(message);
    }

}
void Server::SendAllowClients(QMap<QTcpSocket*,QString> Sockets){
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Version());
    out << 1 << AllowUsers;
    for (auto it = Sockets.constBegin(); it != Sockets.constEnd(); ++it) {
        it.key()->write(Data);
        it.key()->waitForBytesWritten();
    }
}
void Server::sockDisc(){
    qDebug() << "disc";

    QTcpSocket* disconnectedSocket = qobject_cast<QTcpSocket*>(sender());
    if (disconnectedSocket) {
        qDebug() << "Disconnected socket:" << disconnectedSocket;
        this->AllowUsers.remove(Sockets[disconnectedSocket]);
        Sockets.remove(disconnectedSocket);
        disconnectedSocket->deleteLater();
        SendAllowClients(this->Sockets);

    } else {
        qDebug() << "Error: Sender is not a QTcpSocket.";
    }
}

void Server::UpdateMessages(QTcpSocket* senderSock,QString sender, QString reciever){
    Data.clear();
    QString restoreMessage = "";
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Version());
    for (const auto& message : messages){

        if ((message.sender == sender && message.receiver == reciever) || (message.sender == reciever && message.receiver == sender) ){
            restoreMessage += message.content + "\n";
        }
    }
    out << 2 << restoreMessage;
    senderSock->write(Data);
}

void Server::SendToClient(QString str,QVector<QTcpSocket*> messagingUsers){
    Data.clear();
    qDebug() << "Sended" << "\n" << str;
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Version());
    out << 2 << str;
    for (int i = 0; i < messagingUsers.size(); i++){
        messagingUsers[i]->write(Data);
    }
}

Server::~Server(){
    for (auto it = Sockets.constBegin(); it != Sockets.constEnd(); ++it) {
        it.key()->close();
        it.key()->deleteLater();
    }
}

DBServer::~DBServer(){
    for (QTcpSocket* deleteSocket : *clientSockets) {
        deleteSocket->close();
        deleteSocket->deleteLater();
    }
    delete clientSockets;
    delete query;
}
