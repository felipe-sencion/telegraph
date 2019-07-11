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
#include <QHash>
#include "edge.h"
#include <queue>

class Telegraph : public QObject
{
    Q_OBJECT

private:
    std::vector<User> users;
    LoginWindow *loginWindow;
    TelegraphWindow *telegraphWindow;
    QFile db;
    QJsonArray jsonArray;
    QHash<QString, QHash<QString, int> > graph;
    QHash<QString, int> edge;

    size_t findUser(QString name);
    void saveDB();
    void loadDB();
    int findContact(int uIndex, QString name);
    void prim();

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
    void addMessage(int uIndex, int cIndex);
    void findContactMessages(int uIndex, QString contact);
};

#endif // TELEGRAPH_H
