#include "telegraphwindow.h"
#include "ui_telegraphwindow.h"

TelegraphWindow::TelegraphWindow(User *u, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TelegraphWindow)
{
    ui->setupUi(this);
    user = u;
    ui->userLabel->setText("Username: " + user->getUserName());
    ui->phoneLabel->setText("Phone: " + user->getPhone());
}

TelegraphWindow::~TelegraphWindow()
{
    delete ui;
}

void TelegraphWindow::on_profilePB_clicked()
{
    ui->contactsSW->setCurrentIndex(1);
}

void TelegraphWindow::on_backPB_clicked()
{
    ui->contactsSW->setCurrentIndex(0);
}
