#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_password_textChanged(const QString &arg1)
{
    if(ui->password->text().size() > password.size())
    {
        password += ui->password->text()[password.size()];
        hide_password.append("•");
    } else if(ui->password->text().size() < password.size())
    {
        password.remove(-1, 1);
        hide_password.remove(-1, 1);
    }
    ui->password->setText(hide_password);
}

QString LoginDialog::get_login(){
    return ui->login->text();
}
