#include "telegraphwindow.h"
#include "ui_telegraphwindow.h"
#include <QDebug>

TelegraphWindow::TelegraphWindow(User *u, int uIndex, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TelegraphWindow)
{
    ui->setupUi(this);
    user = u;
    userIndex = uIndex;
    ui->userLabel->setText("Username: " + user->getUserName());
    ui->phoneLabel->setText("Phone: " + user->getPhone());
    resetContactList();
}

TelegraphWindow::~TelegraphWindow()
{
    delete ui;
}

void TelegraphWindow::addContactWidget(QString name, bool added)
{
    qDebug()<<"add " <<name;
    QListWidgetItem *newItem = new QListWidgetItem;
    ContactWidget *contact = new ContactWidget(name);
    contact->enableAddPB(added);
    qDebug()<<"enabled " <<name;
    connect(contact, SIGNAL(add(QString)), this, SLOT(addContact(QString)));
    ui->contactsLW->addItem(newItem);
    newItem->setSizeHint(contact->sizeHint());
    //newItem->setBackground(QColor(19, 231, 195));
    ui->contactsLW->setItemWidget(newItem, contact);
    qDebug()<<"added " <<name;
}

void TelegraphWindow::on_profilePB_clicked()
{
    ui->contactsSW->setCurrentIndex(1);
}

void TelegraphWindow::on_backPB_clicked()
{
    ui->contactsSW->setCurrentIndex(0);
}

void TelegraphWindow::on_searchLE_textChanged(const QString &arg1)
{
    ui->contactsLW->clear();
    emit searching(userIndex, arg1);
}

void TelegraphWindow::addContact(QString name)
{
    vector<QString> contacts;
    contacts = user->getContacts();
    contacts.push_back(name);
    user->setContacts(contacts);
    emit updateContacts(userIndex);
    ui->searchLE->clear();
    resetContactList();
}

void TelegraphWindow::resetContactList()
{
    ui->contactsLW->clear();
    vector<QString> contacts = user->getContacts();
    qDebug()<<"contacts " <<contacts.size();
    for (unsigned int i(0); i < contacts.size(); ++i)
        addContactWidget(contacts.at(i), false);
}
