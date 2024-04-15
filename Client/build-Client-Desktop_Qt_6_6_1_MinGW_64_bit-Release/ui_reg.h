/********************************************************************************
** Form generated from reading UI file 'reg.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REG_H
#define UI_REG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Reg
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *Login;
    QLabel *label_2;
    QLineEdit *PasswordEDIT;
    QLabel *label_3;
    QLineEdit *Password2Edit;
    QPushButton *SignUpButton;
    QPushButton *CancleButton;

    void setupUi(QDialog *Reg)
    {
        if (Reg->objectName().isEmpty())
            Reg->setObjectName("Reg");
        Reg->resize(400, 300);
        gridLayout = new QGridLayout(Reg);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(Reg);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        Login = new QLineEdit(Reg);
        Login->setObjectName("Login");

        gridLayout->addWidget(Login, 1, 0, 1, 2);

        label_2 = new QLabel(Reg);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(382, 40));
        label_2->setMaximumSize(QSize(382, 40));

        gridLayout->addWidget(label_2, 2, 0, 1, 2);

        PasswordEDIT = new QLineEdit(Reg);
        PasswordEDIT->setObjectName("PasswordEDIT");

        gridLayout->addWidget(PasswordEDIT, 3, 0, 1, 2);

        label_3 = new QLabel(Reg);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 4, 0, 1, 2);

        Password2Edit = new QLineEdit(Reg);
        Password2Edit->setObjectName("Password2Edit");

        gridLayout->addWidget(Password2Edit, 5, 0, 1, 2);

        SignUpButton = new QPushButton(Reg);
        SignUpButton->setObjectName("SignUpButton");
        SignUpButton->setEnabled(false);

        gridLayout->addWidget(SignUpButton, 6, 0, 1, 2);

        CancleButton = new QPushButton(Reg);
        CancleButton->setObjectName("CancleButton");

        gridLayout->addWidget(CancleButton, 7, 0, 1, 2);


        retranslateUi(Reg);

        QMetaObject::connectSlotsByName(Reg);
    } // setupUi

    void retranslateUi(QDialog *Reg)
    {
        Reg->setWindowTitle(QCoreApplication::translate("Reg", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Reg", "Login", nullptr));
        label_2->setText(QCoreApplication::translate("Reg", "Password", nullptr));
        label_3->setText(QCoreApplication::translate("Reg", "Password", nullptr));
        SignUpButton->setText(QCoreApplication::translate("Reg", "Sign Up", nullptr));
        CancleButton->setText(QCoreApplication::translate("Reg", "Cancle", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Reg: public Ui_Reg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REG_H
