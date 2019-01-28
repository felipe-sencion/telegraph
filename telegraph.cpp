#include "telegraph.h"
#include <QMessageBox>

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
    User u(name, phone, password);
    users.push_back(u);

    QMessageBox message;
    message.setWindowTitle("New User");
    message.setText("New user created");
    message.exec();
}
