#include "loginreg.h"
#include "ui_loginreg.h"
#include <reg.h>

#include <mainwindow.h>
LoginReg::LoginReg(QWidget *parent)

    : QDialog(parent)
    , ui(new Ui::LoginReg)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    socket->connectToHost("26.103.198.212",4444);
    Data.clear();
    qDebug() << socket;
    connect(socket,&QTcpSocket::readyRead,this, &LoginReg::sockReady);
    connect(socket,&QTcpSocket::disconnected,this, &QTcpSocket::deleteLater);
}

LoginReg::~LoginReg()
{
    delete registry;
    delete socket;
    delete ui;
}

void LoginReg::on_SignUpButton_clicked()
{
    registry = new Reg(socket,this);
    registry->show();
    registry->exec();
}

void LoginReg::sockReady(){
    Data.clear();
    Data = socket->readAll();
    QDataStream stream(&Data,QIODevice::ReadOnly);
    bool check;
    qint32 requestNum;
    stream >> check >> requestNum;
    qDebug() << requestNum;
    if  (check == 1 && requestNum == 3){
        registry->check = 1;
    }
    if (check == 1 && requestNum == 1){
        QMessageBox::information(nullptr,"Успех","Все верно");
        MainWindow *Main = new MainWindow;
        Main->LoginWrite(this->Login);
        Main->show();
        this->close();
    }
    else if (check == 0 && requestNum == 1){
        QMessageBox::information(nullptr,"Ошибка","Неверный логин либо пароль");
    }
}


void LoginReg::on_SignInButton_clicked()
{
    if (socket->waitForConnected()){
        Data.clear();
        QDataStream stream(&Data, QIODevice::WriteOnly);
        stream << 1 << this->Login << this->Password;
        socket->write(Data);
        socket->flush();
        socket->waitForBytesWritten();
    }
    else{
        qDebug() << "error";
    }
}


void LoginReg::on_LoginEdit_textChanged(const QString &arg1)
{
    this->Login = arg1;
}


void LoginReg::on_PasswordEdit_textChanged(const QString &arg1)
{
    this->Password = arg1;
}

