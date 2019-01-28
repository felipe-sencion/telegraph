#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::enableLoginPB()
{
    if (ui->userLE->text().length() > 0 && ui->passwordLE->text().length() > 0)
        ui->loginPB->setEnabled(true);
    else
        ui->loginPB->setEnabled(false);
}

void LoginWindow::enableCreatePB()
{
    if (ui->newUserLE->text().length() > 0 && ui->newPasswordLE->text().length() > 0 && ui->phoneLE->text().length() == 10)
        ui->createPB->setEnabled(true);
    else
        ui->createPB->setEnabled(false);
}

void LoginWindow::on_userLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableLoginPB();
}

void LoginWindow::on_passwordLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableLoginPB();
}

void LoginWindow::on_newUserLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableCreatePB();
}

void LoginWindow::on_newPasswordLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableCreatePB();
}

void LoginWindow::on_phoneLE_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    enableCreatePB();
}

void LoginWindow::on_loginPB_clicked()
{
    emit login(ui->userLE->text(), ui->passwordLE->text());
    ui->userLE->clear();
    ui->passwordLE->clear();
}

void LoginWindow::on_createPB_clicked()
{
    emit create(ui->newUserLE->text(), ui->newPasswordLE->text(), ui->phoneLE->text());
    ui->newUserLE->clear();
    ui->phoneLE->clear();
    ui->newPasswordLE->clear();
}
