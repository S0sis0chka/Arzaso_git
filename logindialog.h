#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    ~LoginDialog();

private slots:
    void on_password_textChanged(const QString &arg1);

private:
    Ui::LoginDialog *ui;
    QString password, hide_password;
public:
    QString get_password(){return password;}
    QString get_login();
};

#endif // LOGINDIALOG_H
