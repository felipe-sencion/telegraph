#ifndef TELEGRAPH_H
#define TELEGRAPH_H
#include <vector>
#include "user.h"
#include "loginwindow.h"
#include "telegraphwindow.h"
#include <QObject>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Telegraph : public QObject
{
    Q_OBJECT

private:
    std::vector<User> users;
    LoginWindow *loginWindow;
    TelegraphWindow *telegraphWindow;
    QFile db;
    QJsonArray jsonArray;

    size_t findUser(QString name);
    void saveDB();
    void loadDB();
    bool findContact(int uIndex, QString name);
    //void populateContacts();

public:
    explicit Telegraph(QObject *parent = 0);
    ~Telegraph();
    void start();

signals:

public slots:

private slots:
    void validate(QString name, QString password);
    void newUser(QString name, QString password, QString phone);
    void search(int uIndex, QString pattern);
    void addContact(int uIndex);
};

#endif // TELEGRAPH_H
