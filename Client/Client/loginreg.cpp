#include "loginreg.h"
#include "ui_loginreg.h"
#include <reg.h>
LoginReg::LoginReg(QWidget *parent)

    : QDialog(parent)
    , ui(new Ui::LoginReg)
{
    ui->setupUi(this);

}

LoginReg::~LoginReg()
{
    delete ui;
}

void LoginReg::on_SignUpButton_clicked()
{
    Reg Registration;
    Registration.show();
    Registration.exec();
}

