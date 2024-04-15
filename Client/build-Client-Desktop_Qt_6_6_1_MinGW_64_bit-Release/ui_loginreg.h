/********************************************************************************
** Form generated from reading UI file 'loginreg.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINREG_H
#define UI_LOGINREG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginReg
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *LoginEdit;
    QLabel *label_2;
    QLineEdit *PasswordEdit;
    QPushButton *SignInButton;
    QPushButton *SignUpButton;

    void setupUi(QDialog *LoginReg)
    {
        if (LoginReg->objectName().isEmpty())
            LoginReg->setObjectName("LoginReg");
        LoginReg->resize(376, 176);
        LoginReg->setMinimumSize(QSize(376, 176));
        LoginReg->setMaximumSize(QSize(376, 176));
        gridLayout = new QGridLayout(LoginReg);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(LoginReg);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        LoginEdit = new QLineEdit(LoginReg);
        LoginEdit->setObjectName("LoginEdit");

        gridLayout->addWidget(LoginEdit, 1, 0, 1, 1);

        label_2 = new QLabel(LoginReg);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        PasswordEdit = new QLineEdit(LoginReg);
        PasswordEdit->setObjectName("PasswordEdit");

        gridLayout->addWidget(PasswordEdit, 3, 0, 1, 1);

        SignInButton = new QPushButton(LoginReg);
        SignInButton->setObjectName("SignInButton");
        SignInButton->setEnabled(false);

        gridLayout->addWidget(SignInButton, 4, 0, 1, 1);

        SignUpButton = new QPushButton(LoginReg);
        SignUpButton->setObjectName("SignUpButton");

        gridLayout->addWidget(SignUpButton, 5, 0, 1, 1);


        retranslateUi(LoginReg);

        QMetaObject::connectSlotsByName(LoginReg);
    } // setupUi

    void retranslateUi(QDialog *LoginReg)
    {
        LoginReg->setWindowTitle(QCoreApplication::translate("LoginReg", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LoginReg", "Login", nullptr));
        label_2->setText(QCoreApplication::translate("LoginReg", "Password", nullptr));
        SignInButton->setText(QCoreApplication::translate("LoginReg", "Sign In", nullptr));
        SignUpButton->setText(QCoreApplication::translate("LoginReg", "Sing Up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginReg: public Ui_LoginReg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINREG_H
