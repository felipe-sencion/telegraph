#ifndef CONTACTWIDGET_H
#define CONTACTWIDGET_H

#include <QWidget>

namespace Ui {
class ContactWidget;
}

class ContactWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ContactWidget(QString name, QWidget *parent = 0);
    ~ContactWidget();

    void enableAddPB(bool enable);

private slots:
    void on_addPB_clicked();

private:
    Ui::ContactWidget *ui;

signals:
    void add(QString name);
};

#endif // CONTACTWIDGET_H
