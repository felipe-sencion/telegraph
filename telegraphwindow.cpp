#include "telegraphwindow.h"
#include "ui_telegraphwindow.h"

TelegraphWindow::TelegraphWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TelegraphWindow)
{
    ui->setupUi(this);
}

TelegraphWindow::~TelegraphWindow()
{
    delete ui;
}
