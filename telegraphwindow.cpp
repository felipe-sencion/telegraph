#include "telegraphwindow.h"
#include "ui_telegraphwindow.h"
#include <QDebug>
#include "messagewidget.h"
#include <algorithm>

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
    QListWidgetItem *newItem = new QListWidgetItem;
    ContactWidget *contact = new ContactWidget(name);
    contact->enableAddPB(added);
    connect(contact, SIGNAL(add(QString)), this, SLOT(addContact(QString)));
    ui->contactsLW->addItem(newItem);
    newItem->setSizeHint(contact->sizeHint());
    ui->contactsLW->setItemWidget(newItem, contact);
}

void TelegraphWindow::displayConversation(vector<Message> contactMessages)
{
    cMessages.clear();
    sMessages.clear();
    sMessages = user->getContacts()[ui->contactsLW->currentRow()].getMessages();
    cMessages = contactMessages;
    int i = 0;
    int j = 0;
    while (i < sMessages.size() && j < cMessages.size())
    {
        if (sMessages.at(i) < cMessages.at(j))
        {
            MessageWidget *messageT= new MessageWidget(sMessages.at(i).getText(), sMessages.at(i).getDateTime().toString("dd MM yyyy hh:mm:ss"));

            ui->messagesTW->setRowCount(ui->messagesTW->rowCount()+1);
            ui->messagesTW->setRowHeight(ui->messagesTW->rowCount()-1, messageT->height());
            ui->messagesTW->setColumnWidth(1, messageT->width());
            ui->messagesTW->setCellWidget(ui->messagesTW->rowCount()-1, 1, messageT);
            ++i;
        }
        else
        {
            MessageWidget *messageT= new MessageWidget(cMessages.at(j).getText(), cMessages.at(j).getDateTime().toString("dd MM yyyy hh:mm:ss"));

            ui->messagesTW->setRowCount(ui->messagesTW->rowCount()+1);
            ui->messagesTW->setRowHeight(ui->messagesTW->rowCount()-1, messageT->height());
            ui->messagesTW->setColumnWidth(1, messageT->width());
            messageT->setStyleSheet("background-color: rgb(198, 90, 238);");
            ui->messagesTW->setCellWidget(ui->messagesTW->rowCount()-1, 0, messageT);
            ++j;
        }
    }
    if (i == sMessages.size())
    {
        for (j; j < cMessages.size(); ++j)
        {
            MessageWidget *messageT= new MessageWidget(cMessages.at(j).getText(), cMessages.at(j).getDateTime().toString("dd MM yyyy hh:mm:ss"));

            ui->messagesTW->setRowCount(ui->messagesTW->rowCount()+1);
            ui->messagesTW->setRowHeight(ui->messagesTW->rowCount()-1, messageT->height());
            ui->messagesTW->setColumnWidth(1, messageT->width());
            messageT->setStyleSheet("background-color: rgb(198, 90, 238);");
            ui->messagesTW->setCellWidget(ui->messagesTW->rowCount()-1, 0, messageT);
        }
    }
    else
    {
        for (i; i < sMessages.size(); ++i)
        {
            MessageWidget *messageT= new MessageWidget(sMessages.at(i).getText(), sMessages.at(i).getDateTime().toString("dd MM yyyy hh:mm:ss"));

            ui->messagesTW->setRowCount(ui->messagesTW->rowCount()+1);
            ui->messagesTW->setRowHeight(ui->messagesTW->rowCount()-1, messageT->height());
            ui->messagesTW->setColumnWidth(1, messageT->width());
            ui->messagesTW->setCellWidget(ui->messagesTW->rowCount()-1, 1, messageT);
        }
    }
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
    ui->messagesSW->setCurrentIndex(0);
    if (arg1.length() > 0)
        emit searching(userIndex, arg1);
    else
        resetContactList();
}

void TelegraphWindow::addContact(QString name)
{
    vector<Contact> contacts;
    contacts = user->getContacts();
    Contact c;
    c.setName(name);
    contacts.push_back(c);
    user->setContacts(contacts);
    emit updateContacts(userIndex);
    ui->searchLE->clear();
    resetContactList();
}

void TelegraphWindow::resetContactList()
{
    ui->contactsLW->clear();
    vector<Contact> contacts = user->getContacts();
    qDebug()<<"contacts " <<contacts.size();
    for (unsigned int i(0); i < contacts.size(); ++i)
        addContactWidget(contacts.at(i).getName(), false);
    ui->messagesSW->setCurrentIndex(0);
}

void TelegraphWindow::loadMessages()
{
    Contact contact = user->getContacts()[ui->contactsLW->currentRow()];
    for (Message m : contact.getMessages())
    {
        MessageWidget *messageT= new MessageWidget(m.getText(), m.getDateTime().toString("dd MM yyyy hh:mm:ss"));

        ui->messagesTW->setRowCount(ui->messagesTW->rowCount()+1);
        ui->messagesTW->setRowHeight(ui->messagesTW->rowCount()-1, messageT->height());
        ui->messagesTW->setColumnWidth(1, messageT->width());
        ui->messagesTW->setCellWidget(ui->messagesTW->rowCount()-1, 1, messageT);
    }
}

void TelegraphWindow::on_contactsLW_itemSelectionChanged()
{
    if (ui->searchLE->text().length() == 0)
    {
        ui->messagesSW->setCurrentIndex(1);
        ui->messagesTW->clear();
        ui->messagesTW->setRowCount(0);
        emit getContactMessages(userIndex, user->getContacts()[ui->contactsLW->currentRow()].getName());
    }
}

void TelegraphWindow::on_sendPB_clicked()
{
    QString text;
    QDateTime date;
    Message m;
    vector<Contact> contacts = user->getContacts();
    Contact c = contacts[ui->contactsLW->currentRow()];
    vector<Message> ms = c.getMessages();

    text = ui->messagePTE->toPlainText();
    date = QDateTime::currentDateTime();
    m.setText(text);
    m.setDateTime(date);
    ms.push_back(m);
    c.setMessages(ms);
    contacts[ui->contactsLW->currentRow()] = c;
    user->setContacts(contacts);

    emit updateMessages(userIndex, ui->contactsLW->currentRow());

    QTableWidgetItem *newT = new QTableWidgetItem;
    MessageWidget *messageT= new MessageWidget(text, date.toString("dd MM yyyy hh:mm:ss"));

    newT->setSizeHint(messageT->sizeHint());
    ui->messagesTW->setRowCount(ui->messagesTW->rowCount()+1);
    ui->messagesTW->setRowHeight(ui->messagesTW->rowCount()-1, messageT->height());
    ui->messagesTW->setColumnWidth(1, messageT->width());
    ui->messagesTW->setCellWidget(ui->messagesTW->rowCount()-1, 1, messageT);
    ui->messagePTE->clear();
}

void TelegraphWindow::on_messagePTE_textChanged()
{
    if (ui->messagePTE->toPlainText().length() > 0)
        ui->sendPB->setEnabled(true);
    else
        ui->sendPB->setEnabled(false);
}

void TelegraphWindow::on_searchMessageLE_textChanged(const QString &arg1)
{
    ui->messagesTW->clear();
    ui->messagesTW->setRowCount(0);
    if (arg1.size() == 0)
    {
        displayConversation(cMessages);
    }
    else
    {
        int i = 0;
        int j = 0;
        while (i < sMessages.size() && j < cMessages.size())
        {
            if (sMessages.at(i) < cMessages.at(j))
            {
                if (sMessages.at(i).getText().contains(arg1, Qt::CaseInsensitive))
                {
                    MessageWidget *messageT= new MessageWidget(sMessages.at(i).getText(), sMessages.at(i).getDateTime().toString("dd MM yyyy hh:mm:ss"));
                    ui->messagesTW->setRowCount(ui->messagesTW->rowCount()+1);
                    ui->messagesTW->setRowHeight(ui->messagesTW->rowCount()-1, messageT->height());
                    ui->messagesTW->setColumnWidth(1, messageT->width());
                    ui->messagesTW->setCellWidget(ui->messagesTW->rowCount()-1, 1, messageT);
                }
                ++i;
            }
            else
            {
                if (cMessages.at(j).getText().contains(arg1, Qt::CaseInsensitive))
                {
                    MessageWidget *messageT= new MessageWidget(cMessages.at(j).getText(), cMessages.at(j).getDateTime().toString("dd MM yyyy hh:mm:ss"));
                    ui->messagesTW->setRowCount(ui->messagesTW->rowCount()+1);
                    ui->messagesTW->setRowHeight(ui->messagesTW->rowCount()-1, messageT->height());
                    ui->messagesTW->setColumnWidth(1, messageT->width());
                    messageT->setStyleSheet("background-color: rgb(198, 90, 238);");
                    ui->messagesTW->setCellWidget(ui->messagesTW->rowCount()-1, 0, messageT);
                }
                ++j;
            }
        }
        if (i == sMessages.size())
        {
            for (j; j < cMessages.size(); ++j)
            {
                if (cMessages.at(j).getText().contains(arg1, Qt::CaseInsensitive))
                {
                    MessageWidget *messageT= new MessageWidget(cMessages.at(j).getText(), cMessages.at(j).getDateTime().toString("dd MM yyyy hh:mm:ss"));
                    ui->messagesTW->setRowCount(ui->messagesTW->rowCount()+1);
                    ui->messagesTW->setRowHeight(ui->messagesTW->rowCount()-1, messageT->height());
                    ui->messagesTW->setColumnWidth(1, messageT->width());
                    messageT->setStyleSheet("background-color: rgb(198, 90, 238);");
                    ui->messagesTW->setCellWidget(ui->messagesTW->rowCount()-1, 0, messageT);
                }
            }
        }
        else
        {
            for (i; i < sMessages.size(); ++i)
            {
                if (sMessages.at(i).getText().contains(arg1, Qt::CaseInsensitive))
                {
                    MessageWidget *messageT= new MessageWidget(sMessages.at(i).getText(), sMessages.at(i).getDateTime().toString("dd MM yyyy hh:mm:ss"));
                    ui->messagesTW->setRowCount(ui->messagesTW->rowCount()+1);
                    ui->messagesTW->setRowHeight(ui->messagesTW->rowCount()-1, messageT->height());
                    ui->messagesTW->setColumnWidth(1, messageT->width());
                    ui->messagesTW->setCellWidget(ui->messagesTW->rowCount()-1, 1, messageT);
                }
            }
        }
    }
}
