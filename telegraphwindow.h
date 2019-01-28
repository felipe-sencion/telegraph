#ifndef TELEGRAPHWINDOW_H
#define TELEGRAPHWINDOW_H
#include "user.h"
#include <QMainWindow>

namespace Ui {
class TelegraphWindow;
}

class TelegraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TelegraphWindow(User *u, QWidget *parent = 0);
    ~TelegraphWindow();

private slots:
    void on_profilePB_clicked();

    void on_backPB_clicked();

private:
    Ui::TelegraphWindow *ui;
    User *user;
};

#endif // TELEGRAPHWINDOW_H
