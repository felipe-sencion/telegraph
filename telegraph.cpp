#include "telegraph.h"
#include <QMessageBox>
#include <QDebug>

size_t Telegraph::findUser(QString name)
{
    size_t idx = 0;
    for (; idx < users.size(); ++idx)
        if (users[idx].getUserName() == name)
            return idx;
    return idx;
}

void Telegraph::saveDB()
{
    if (!db.open(QIODevice::WriteOnly))
    {
        QMessageBox message;
        message.setWindowTitle("Error");
        message.setText("Couldn't open database");
        message.exec();
    }
    else
    {
        QJsonObject jsonObject;
        jsonObject["users"] = jsonArray;
        QJsonDocument jsonDocument(jsonObject);
        db.write(jsonDocument.toJson());
    }
    db.close();
}

void Telegraph::loadDB()
{
    if (!db.open(QIODevice::ReadOnly))
    {
        QMessageBox message;
        message.setWindowTitle("Error");
        message.setText("Couldn't open database");
        message.exec();
    }
    else
    {
        QByteArray data = db.readAll();
        QJsonDocument jsonDocument(QJsonDocument::fromJson(data));
        QJsonObject jsonObject = jsonDocument.object();
        jsonArray = jsonObject["users"].toArray();
        for (int i(0); i < jsonArray.size(); ++i)
        {
            QJsonObject obj = jsonArray[i].toObject();
            User u(obj["userName"].toString(), obj["phone"].toString(), obj["password"].toString());
            QJsonArray contactsArray = obj["contacts"].toArray();
            vector<Contact> contacts;
            for(int i(0); i < contactsArray.size(); ++i)
            {
                Contact contact;
                QString name = contactsArray[i].toObject()["name"].toString();
                QJsonArray messagesArray = contactsArray[i].toObject()["messages"].toArray();
                vector<Message> ms;
                for (int j(0); j < messagesArray.size(); ++j)
                {
                    Message m;
                    m.setText(messagesArray[j].toObject()["text"].toString());
                    m.setDateTime(QDateTime::fromString(messagesArray[j].toObject()["date"].toString(), "ddMMyyyy hh:mm:ss"));
                    ms.push_back(m);

                }
                contact.setName(name);
                contact.setMessages(ms);
                contacts.push_back(contact);
            }
            u.setContacts(contacts);

            users.push_back(u);
        }
    }
    db.close();
}

bool Telegraph::findContact(int uIndex, QString name)
{
    vector<Contact> contacts = users.at((uIndex)).getContacts();
    for (int i(0); i < contacts.size(); ++i)
    {
        if (contacts.at(i).getName() == name)
            return true;
    }
    return false;
}

/*void Telegraph::populateContacts()
{
    for (unsigned int i(0); i < users.size(); ++i)
        telegraphWindow->addContactWidget(users[i].getUserName());
}*/

Telegraph::Telegraph(QObject *parent) : QObject(parent)
{
    loginWindow = new LoginWindow();
    connect(loginWindow, SIGNAL(login(QString,QString)), this, SLOT(validate(QString,QString)));
    connect(loginWindow, SIGNAL(create(QString,QString,QString)), this, SLOT(newUser(QString,QString,QString)));
    db.setFileName("telegraph.json");
    loadDB();
}

Telegraph::~Telegraph()
{
    saveDB();
}

void Telegraph::start()
{
    loginWindow->show();
}

void Telegraph::validate(QString name, QString password)
{
    unsigned int i;
    for (i = 0; i < users.size(); ++i)
    {
        if (users[i].getUserName() == name && users[i].getPassword() == password)
        {
            telegraphWindow = new TelegraphWindow(&users[i], i);
            connect(telegraphWindow, SIGNAL(searching(int, QString)), this, SLOT(search(int, QString)));
            connect(telegraphWindow, SIGNAL(updateContacts(int)), this, SLOT(addContact(int)));
            connect(telegraphWindow, SIGNAL(updateMessages(int,int)), this, SLOT(addMessage(int,int)));
            telegraphWindow->show();
            //populateContacts();
            break;
        }
    }
    if (i == users.size())
    {
        QMessageBox message;
        message.setWindowTitle("Error");
        message.setText("Invalid username or password");
        message.exec();
    }
}

void Telegraph::newUser(QString name, QString password, QString phone)
{
    if (findUser(name) < users.size())
    {
        QMessageBox message;
        message.setWindowTitle("User already exists");
        message.setText("The username is already being used");
        message.exec();
    }
    else
    {
        User u(name, phone, password);
        users.push_back(u);
        QJsonObject jsonObject;
        jsonObject["userName"] = name;
        jsonObject["phone"] = phone;
        jsonObject["password"] = password;
        QJsonArray contactsArray;
        jsonObject["contacts"] = contactsArray;
        jsonArray.append(jsonObject);

        QMessageBox message;
        message.setWindowTitle("New User");
        message.setText("New user created");
        message.exec();
    }
}

void Telegraph::search(int uIndex, QString pattern)
{
    for (unsigned int i(0); i < users.size(); ++i)
        if (users.at(i).getUserName().contains(pattern, Qt::CaseInsensitive))
        {
            if (findContact(uIndex, users.at(i).getUserName()))
                telegraphWindow->addContactWidget(users[i].getUserName(), false);
            else
                telegraphWindow->addContactWidget(users[i].getUserName(), true);
        }
}

void Telegraph::addContact(int uIndex)
{
    QJsonObject obj = jsonArray[uIndex].toObject();
    QJsonArray contactsArray = obj["contacts"].toArray();
    vector<Contact> contacts = users[uIndex].getContacts();
    QJsonObject contact;
    contact["name"] = contacts.at(contacts.size()-1).getName();
    QJsonArray messagesArray;
    contact["messages"] = messagesArray;
    contactsArray.append(contact);
    obj["contacts"] = contactsArray;
    jsonArray[uIndex] = obj;
}

void Telegraph::addMessage(int uIndex, int cIndex)
{
    QJsonObject obj = jsonArray[uIndex].toObject();
    QJsonArray contactsArray = obj["contacts"].toArray();
    vector<Contact> contacts = users[uIndex].getContacts();
    QJsonObject contact = contactsArray[cIndex].toObject();
    //contact["name"] = contacts.at(contacts.size()-1).getName();
    QJsonArray messagesArray = contact["messages"].toArray();
    QJsonObject messageObj;
    vector<Message> ms = contacts[cIndex].getMessages();
    messageObj["text"] = ms[ms.size()-1].getText();
    messageObj["date"] = ms[ms.size()-1].getDateTime().toString("ddMMyyyy hh:mm:ss");
    messagesArray.append(messageObj);

    contact["messages"] = messagesArray;
    contactsArray[cIndex] = contact;
    obj["contacts"] = contactsArray;
    jsonArray[uIndex] = obj;
}
