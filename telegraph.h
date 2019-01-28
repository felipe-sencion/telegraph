#ifndef TELEGRAPH_H
#define TELEGRAPH_H
#include <vector>
#include "user.h"
#include "loginwindow.h"
#include "telegraphwindow.h"
#include <QObject>

class Telegraph : public QObject
{
    Q_OBJECT

private:
    std::vector<User> users;
    LoginWindow *loginWindow;
    TelegraphWindow *telegraphWindow;

public:
    explicit Telegraph(QObject *parent = 0);
    void start();

signals:

public slots:

private slots:
    void validate(QString name, QString password);
    void newUser(QString name, QString password, QString phone);
};

#endif // TELEGRAPH_H
