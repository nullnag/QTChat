#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlistwidget.h"
#include <QMainWindow>
#include <QTcpSocket>
#include <QMap>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_lineEdit_returnPressed();

    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    QString Login;
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    QByteArray Data;
    QString ChosenUser;
    void SendToServer(QString str, QString ChosenUser);
    quint16 nextBlockSize;
public slots:
    void LoginWrite(QString login);
    void sockReady();
};

#endif // MAINWINDOW_H
