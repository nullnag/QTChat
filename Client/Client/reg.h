#ifndef REG_H
#define REG_H

#include <QDialog>
#include <QTcpSocket>
namespace Ui {
class Reg;
}

class Reg : public QDialog
{
    Q_OBJECT

public:
    explicit Reg(QWidget *parent = nullptr);
    ~Reg();
private:
    QTcpSocket socket;
    bool PassCheck = 0;
    bool LoginCheck = 0;
    QString pass1 = "";
    QString pass2 = "";
    QString Login = "";
private slots:
    void on_Login_textEdited(const QString &arg1);

    void SignUpButtonEn(const bool &LoginCheck, const bool &PassCheck);

    void on_PasswordEDIT_textChanged(const QString &arg1);

    void on_Password2Edit_textChanged(const QString &arg1);

    void on_CancleButton_clicked();

    void on_SignUpButton_pressed();

private:
    Ui::Reg *ui;
};

#endif // REG_H
