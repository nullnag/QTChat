#ifndef LOGINREG_H
#define LOGINREG_H

#include <QDialog>
namespace Ui {
class LoginReg;
}

class LoginReg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginReg(QWidget *parent = nullptr);
    ~LoginReg();

private slots:
    void on_SignUpButton_clicked();

private:
    Ui::LoginReg *ui;
};

#endif // LOGINREG_H
