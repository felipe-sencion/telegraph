#ifndef USER_H
#define USER_H
#include <iostream>
#include <QString>
#include <vector>
#include "contact.h"

using namespace std;

class User
{
private:
    QString userName;
    QString phone;
    QString password;
    vector<Contact> contacts;

public:
    User(QString name, QString ph, QString pass);
    QString getUserName() const;
    void setUserName(const QString &value);
    QString getPhone() const;
    void setPhone(const QString &value);
    QString getPassword() const;
    void setPassword(const QString &value);
    vector<Contact> getContacts() const;
    void setContacts(const vector<Contact> &value);
};

#endif // USER_H
