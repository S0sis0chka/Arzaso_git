#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDialog>
#include "logindialog.h"
#include "coder.cpp"
#include <QMessageBox>
#include "translitter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QDir main_dir(QDir::homePath());
    main_dir.mkdir(".СистемаЗачётов");
    main_dir.setPath(QDir::homePath() + "\\.СистемаЗачётов");
    main_dir.mkdir("tmp");
    main_dir.mkdir(".history");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_btn_triggered()
{
    LoginDialog * login_form = new LoginDialog();
    int answer = login_form->exec();
    if(answer == QDialog::Accepted){
        //******************
        //Connect to server
        QDir folder(home_path + "\\.СистемаЗачётов");
        if (!folder.exists("number_" + login_form->get_login()))
        {
                qWarning()<<"Саня не клоун";
                QFile file;
                file.setFileName(home_path + "\\.СистемаЗачётов\\number_" + login_form->get_login());
                file.open(QIODevice::WriteOnly | QIODevice::Text);
                file.write("0");
                file.close();
        }
        QFile file;
        file.setFileName(home_path + "\\.СистемаЗачётов\\number_" + login_form->get_login());
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        long long number = file.readAll().toLongLong();
        file.close();
        QString login_encode = encode(login_form->get_login(), number);
        QString password_encode = encode(login_form->get_password(), number);
        //qWarning()<< password_encode;
        //qWarning() << login_encode;
        socket->connectToHost("alexavr.ru", 25555, QTcpSocket::ReadWrite);
        socket->waitForConnected();
        socket->write(QString("com://connect " + login_encode + "&&" + password_encode).toLocal8Bit());
        socket->waitForReadyRead();
        QByteArray data = socket->readAll();
        //
        //******************
        qWarning()<<data;
        if(data == "ok"){
            number = gen(number);
            file.open(QIODevice::WriteOnly | QIODevice::Text);
            file.write(QString::number(number).toLocal8Bit());
            file.close();
            socket->waitForReadyRead();
            data = socket->readAll();
            person_type = data.split(' ')[0];
            class_num = Translit->fromTranslit(data.split(' ')[1]);
            login = login_form->get_login();
            username = Translit->fromTranslit(data.split(' ')[2]);
            username.replace("_", "\n");
            if(data.split(' ').size() == 4){
                file.open(QIODevice::WriteOnly | QIODevice::Text);
                file.write(data.split(' ')[3]);
                file.close();
            }
            ui->userinfo->setText(username + "\n" + class_num);
            delete login_form;
        }
        socket->close();
        if(person_type == "teacher"){

        } else if(person_type == "student"){
            update_mark();
        }
    }     
}

void MainWindow::on_exit_triggered()
{
    close();
}

void MainWindow::update_mark()
{
    //qWarning()<<login;
    if (login != "")
    {
        //qWarning()<<"1";
        socket->connectToHost("alexavr.ru", 25555, QTcpSocket::ReadWrite);
        socket->waitForConnected();
        QFile file;
        file.setFileName(home_path + "\\.СистемаЗачётов\\number_" + login);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        long long number = file.readAll().toLongLong();
        file.close();
        //qWarning()<<"2";
        QString login_encode = encode(login, number);
        //qWarning()<<QString("com://give_marks/" + login_encode);
        socket->write(QString("com://give_marks/" + login_encode).toLocal8Bit());
        socket->waitForBytesWritten();
        socket->waitForReadyRead();
        QByteArray data = socket->readAll();
        //qWarning()<<data;
        socket->close();
        //qWarning()<<data.split('$');
        //qWarning()<<toTranslit("Биология, Индивидуальный проект,")
        //QMap<QString, QString> tuble;
        foreach(QString i, data.split('$'))
        {
            QList row = i.split(';');
            QString lesson = row[1];
            QString otmet = row[4];
            //qWarning()<<lesson;
            //qWarning()<<otmet;
            if (lesson == Translit->toTranslit("Математика"))
            {
                if (ui->algebra->text() == "")
                {
                    ui->algebra->setText(Translit->fromTranslit(otmet));
                }
                else ui->algebra->setText(ui->algebra->text() + ", " + Translit->fromTranslit(otmet));
            }
            else if (lesson == Translit->toTranslit("Биология"))
            {
                if (ui->biologia->text() == "")
                {
                    ui->biologia->setText(Translit->fromTranslit(otmet));
                }
                else ui->biologia->setText(ui->biologia->text() + ", " + Translit->fromTranslit(otmet));
            }
            else if (lesson == Translit->toTranslit("Индивидуальный проект"))
            {
                if (ui->individual->text() == "")
                {
                    ui->individual->setText(Translit->fromTranslit(otmet));
                }
                else ui->individual->setText(ui->individual->text() + ", " + Translit->fromTranslit(otmet));
            }
            else if (lesson == Translit->toTranslit("Информатика"))
            {
                if (ui->informat->text() == "")
                {
                    ui->informat->setText(Translit->fromTranslit(otmet));
                }
                else ui->informat->setText(ui->informat->text() + ", " + Translit->fromTranslit(otmet));
            }
            else if (lesson == Translit->toTranslit("История"))
            {
                if (ui->istoria->text() == "")
                {
                    ui->istoria->setText(Translit->fromTranslit(otmet));
                }
                else ui->istoria->setText(ui->istoria->text() + ", " + Translit->fromTranslit(otmet));
            }
            else if (lesson == Translit->toTranslit("Литература"))
            {
                if (ui->literat->text() == "")
                {
                    ui->literat->setText(Translit->fromTranslit(otmet));
                }
                else ui->literat->setText(ui->literat->text() + ", " + Translit->fromTranslit(otmet));
            }
            else if (lesson == Translit->toTranslit("Обществознание"))
            {
                if (ui->obzestvo->text() == "")
                {
                    ui->obzestvo->setText(Translit->fromTranslit(otmet));
                }
                else ui->obzestvo->setText(ui->obzestvo->text() + ", " + Translit->fromTranslit(otmet));
            }
            else if (lesson == Translit->toTranslit("ОБЖ"))
            {
                if (ui->obz->text() == "")
                {
                    ui->obz->setText(Translit->fromTranslit(otmet));
                }
                else ui->obz->setText(ui->obz->text() + ", " + Translit->fromTranslit(otmet));
            }
            else if (lesson == Translit->toTranslit("Русский язык"))
            {
                if (ui->russkiy->text() == "")
                {
                    ui->russkiy->setText(Translit->fromTranslit(otmet));
                }
                else ui->russkiy->setText(ui->russkiy->text() + ", " + Translit->fromTranslit(otmet));
            }
            else if (lesson == Translit->toTranslit("Русский язык"))
            {
                if (ui->phizika->text() == "")
                {
                    ui->phizika->setText(Translit->fromTranslit(otmet));
                }
                else ui->phizika->setText(ui->phizika->text() + ", " + Translit->fromTranslit(otmet));
            }
            else if (lesson == Translit->toTranslit("Физкультура"))
            {
                if (ui->phizra->text() == "")
                {
                    ui->phizra->setText(Translit->fromTranslit(otmet));
                }
                else ui->phizra->setText(ui->phizra->text() + ", " + Translit->fromTranslit(otmet));
            }
            else if (lesson == Translit->toTranslit("Химия"))
            {
                if (ui->himiya->text() == "")
                {
                    ui->himiya->setText(Translit->fromTranslit(otmet));
                }
                else ui->himiya->setText(ui->himiya->text() + ", " + Translit->fromTranslit(otmet));
            }
        }
    }
}


void MainWindow::on_obnovit_triggered()
{
    ui->algebra->setText("");
    ui->biologia->setText("");
    ui->individual->setText("");
    ui->informat->setText("");
    ui->istoria->setText("");
    ui->literat->setText("");
    ui->obzestvo->setText("");
    ui->obz->setText("");
    ui->russkiy->setText("");
    ui->phizika->setText("");
    ui->phizra->setText("");
    ui->himiya->setText("");
    update_mark();
}

