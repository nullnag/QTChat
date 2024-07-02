#include "reg.h"
#include "ui_reg.h"
#include <QMessageBox>


Reg::Reg(QTcpSocket* socket,QWidget *parent)

    : QDialog(parent)
    , ui(new Ui::Reg)
{
    ui->setupUi(this);
    this->socket = socket;
    connect(this->socket,&QTcpSocket::readyRead,this, &Reg::sockReady);
    connect(this->socket,&QTcpSocket::disconnected,this, &QTcpSocket::deleteLater);
}

Reg::~Reg()
{
    delete ui;
    delete socket;
}

void Reg::sockReady(){

    if (this->check == 1){
        QMessageBox::information(nullptr,"Ошибка","Данный логин уже существует");
        this->LoginCheck = 0;
        SignUpButtonEn(this->LoginCheck, this->PassCheck);
    }

}

void Reg::on_Login_textEdited(const QString &arg1)
{
    this->check = 0;
    this->Login = arg1;
    if (arg1.length() >= 6){
        this->LoginCheck = 1;
    }
    else{
        this->LoginCheck = 0;
    }
    Data.clear();
    QDataStream request(&Data,QIODevice::WriteOnly);
    request << 3 << this->Login;
    this->socket->write(Data);
    this->socket->flush();
    this->socket->waitForBytesWritten();
    SignUpButtonEn(this->LoginCheck, this->PassCheck);
}


void Reg::SignUpButtonEn(const bool &LoginCheck, const bool &PassCheck){
    if (LoginCheck && PassCheck){
        ui->SignUpButton->setEnabled(true);
    }
    else{
        ui->SignUpButton->setEnabled(false);
    }


}

void Reg::on_PasswordEDIT_textChanged(const QString &arg1)
{
    this->pass1 = arg1;
    if (pass1.length() >= 8 && this->pass1 == this-> pass2){
        this->PassCheck = 1;
    }
    else{
        this->PassCheck = 0;
    }
    SignUpButtonEn(this->LoginCheck, this->PassCheck);
}

void Reg::on_Password2Edit_textChanged(const QString &arg1)
{
    this->pass2 = arg1;
    if (pass2.length() >= 8 && this->pass1 == this-> pass2){
        this->PassCheck = 1;
    }
    else{
        this->PassCheck = 0;
    }
    SignUpButtonEn(this->LoginCheck, this->PassCheck);
}

void Reg::on_CancleButton_clicked()
{
    close();
}


void Reg::on_SignUpButton_pressed()
{
    if (socket->waitForConnected()){
        Data.clear();
        QDataStream stream(&Data, QIODevice::WriteOnly);
        stream << 2 << this->Login << this->pass2;
        socket->write(Data);
        socket->flush();
        socket->waitForBytesWritten();
        QMessageBox::information(nullptr,"Успешная регистрация","Вы успешно зарегистрировались");
        close();

    }
    else{
        qDebug() << "error";
    }
}




