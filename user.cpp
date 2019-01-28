#include "user.h"

QString User::getUserName() const
{
    return userName;
}

void User::setUserName(const QString &value)
{
    userName = value;
}

QString User::getPhone() const
{
    return phone;
}

void User::setPhone(const QString &value)
{
    phone = value;
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &value)
{
    password = value;
}

User::User(QString name, QString ph, QString pass)
{
    userName = name;
    phone = ph;
    password = pass;
}
