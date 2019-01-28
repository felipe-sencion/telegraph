#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_userLE_textChanged(const QString &arg1);

    void on_passwordLE_textChanged(const QString &arg1);

    void on_newUserLE_textChanged(const QString &arg1);

    void on_newPasswordLE_textChanged(const QString &arg1);

    void on_phoneLE_textChanged(const QString &arg1);

    void on_loginPB_clicked();

    void on_createPB_clicked();

private:
    Ui::LoginWindow *ui;

    void enableLoginPB();
    void enableCreatePB();

signals:
    void login(QString user, QString password);
    void create(QString user, QString password, QString phone);
};

#endif // LOGINWINDOW_H
