#include "telegraph.h"
#include <QMessageBox>

size_t Telegraph::findUser(QString name)
{
    size_t idx = 0;
    for (; idx < users.size(); ++idx)
        if (users[idx].getUserName() == name)
            return idx;
    return idx;
}

Telegraph::Telegraph(QObject *parent) : QObject(parent)
{
    loginWindow = new LoginWindow();
    connect(loginWindow, SIGNAL(login(QString,QString)), this, SLOT(validate(QString,QString)));
    connect(loginWindow, SIGNAL(create(QString,QString,QString)), this, SLOT(newUser(QString,QString,QString)));
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
            telegraphWindow = new TelegraphWindow(&users[i]);
            telegraphWindow->show();
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

        QMessageBox message;
        message.setWindowTitle("New User");
        message.setText("New user created");
        message.exec();
    }
}
