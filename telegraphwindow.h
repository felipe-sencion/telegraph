#ifndef TELEGRAPHWINDOW_H
#define TELEGRAPHWINDOW_H
#include "user.h"
#include <QMainWindow>
#include "contactwidget.h"
#include <QListWidgetItem>

namespace Ui {
class TelegraphWindow;
}

class TelegraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TelegraphWindow(User *u, int uIndex, QWidget *parent = 0);
    ~TelegraphWindow();

    void addContactWidget(QString name, bool added);

private slots:
    void on_profilePB_clicked();

    void on_backPB_clicked();

    void on_searchLE_textChanged(const QString &arg1);

    void addContact(QString name);

    void on_contactsLW_itemSelectionChanged();

    void on_sendPB_clicked();

    void on_messagePTE_textChanged();

private:
    Ui::TelegraphWindow *ui;
    User *user;
    int userIndex;

    void resetContactList();
    void loadMessages();
signals:
    void searching(int uIdx, QString pattern);

    void updateContacts(int uIdx);

    void updateMessages(int uIdx, int cIdx);
};

#endif // TELEGRAPHWINDOW_H
