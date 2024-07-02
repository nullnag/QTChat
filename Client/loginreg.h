#ifndef LOGINREG_H
#define LOGINREG_H

#include <QDialog>
#include<QMessageBox>
#include <QTcpSocket>
#include<reg.h>
namespace Ui {
class LoginReg;
}

class LoginReg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginReg(QWidget *parent = nullptr);
    ~LoginReg();

    QTcpSocket* getSock() const{
        return socket;
    }

private slots:
    void on_SignUpButton_clicked();

    void on_SignInButton_clicked();

    void on_LoginEdit_textChanged(const QString &arg1);

    void on_PasswordEdit_textChanged(const QString &arg1);

    void sockReady();

private:
    QTcpSocket* socket;
    QString Login;
    QString Password;
    QByteArray Data;
    Ui::LoginReg *ui;
    Reg* registry;
};

#endif // LOGINREG_H
