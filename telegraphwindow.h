#ifndef TELEGRAPHWINDOW_H
#define TELEGRAPHWINDOW_H

#include <QMainWindow>

namespace Ui {
class TelegraphWindow;
}

class TelegraphWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TelegraphWindow(QWidget *parent = 0);
    ~TelegraphWindow();

private:
    Ui::TelegraphWindow *ui;
};

#endif // TELEGRAPHWINDOW_H
