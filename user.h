#ifndef USER_H
#define USER_H
#include <iostream>
#include <QString>
#include <vector>

using namespace std;

class User
{
private:
    QString userName;
    QString phone;
    QString password;
    vector<QString> contacts;

public:
    User(QString name, QString ph, QString pass);
    QString getUserName() const;
    void setUserName(const QString &value);
    QString getPhone() const;
    void setPhone(const QString &value);
    QString getPassword() const;
    void setPassword(const QString &value);
    vector<QString> getContacts() const;
    void setContacts(const vector<QString> &value);
};

#endif // USER_H
