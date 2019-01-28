#ifndef USER_H
#define USER_H
#include <iostream>
#include <QString>

class User
{
private:
    QString userName;
    QString phone;
    QString password;

public:
    User(QString name, QString ph, QString pass);
    QString getUserName() const;
    void setUserName(const QString &value);
    QString getPhone() const;
    void setPhone(const QString &value);
    QString getPassword() const;
    void setPassword(const QString &value);
};

#endif // USER_H
