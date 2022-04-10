#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QtNetwork/QTcpSocket>
#include "translitter.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_login_btn_triggered();
    void on_exit_triggered();

    void on_obnovit_triggered();

private:
    Ui::MainWindow *ui;
    QString home_path = QDir::homePath();
    QTcpSocket *socket = new QTcpSocket();
    Translitter * Translit = new Translitter();
    QString username;
    QString login;
    QString class_num;
    QString person_type;
    void update_mark();
};
#endif // MAINWINDOW_H
