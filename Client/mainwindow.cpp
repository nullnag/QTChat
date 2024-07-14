#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::readyRead,this, &MainWindow::sockReady);
    connect(socket,&QTcpSocket::disconnected,socket, &QTcpSocket::deleteLater);
}

MainWindow::~MainWindow()
{
    delete socket;
    delete ui;
}


void MainWindow::LoginWrite(QString login){
    this->Login = login;
}

void MainWindow::on_pushButton_clicked()
{
    socket->connectToHost("26.103.198.212",5555);
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Version());
    out << 1 << Login;
    socket->write(Data);
}

void MainWindow::SendToServer(QString str, QString ChosenUser)
{
    Data.clear();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Version());
    out << 2 << str << ChosenUser;
    socket->write(Data);
    ui->lineEdit->clear();
}

void MainWindow::sockReady()
{
    qDebug() << "get";
    QDataStream in(socket);
    in.setVersion(QDataStream::Version());
    qint32 requestNum = 0;
    QString str = "";
    QSet<QString> Users = {};

    in >> requestNum;
    qDebug() << requestNum << " Текущий процесс";
    switch (requestNum) {
    case 1:
        in >> Users;
        ui->listWidget->clear();
        for (auto it = Users.constBegin(); it != Users.constEnd(); ++it) {
            qDebug() << *it << " ";
            if (*it == Login){
                ui->NickNameBar->append(*it);
                continue;
            }
            new QListWidgetItem(*it, ui->listWidget);
        }
        break;
    case 2:
        in >> str;
        qDebug() << str;
        ui->textBrowser->append(str);
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ui->lineEdit->text().length() > 0 && ChosenUser.length() != 0){
        SendToServer( Login + '\n' + ui->lineEdit->text() + '\n',ChosenUser);
    }

}

void MainWindow::on_lineEdit_returnPressed()
{
    if (ui->lineEdit->text().length() > 0 && ChosenUser.length() != 0){
        SendToServer( Login + '\n' + ui->lineEdit->text() + '\n', ChosenUser);
    }
}

void MainWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    ui->textBrowser->clear();
    Data.clear();
    ChosenUser = item->text();
    QDataStream out(&Data, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Version());
    out << 3 << Login << ChosenUser;
    socket->write(Data);

}

