#include "messagewidget.h"
#include "ui_messagewidget.h"
#include <QPainterPath>
#include <QRegion>

MessageWidget::MessageWidget(QString text, QString date, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MessageWidget)
{
    ui->setupUi(this);


    const int radius = 30;

    QPainterPath path;
    path.addRoundedRect(rect(), radius, radius);
    QRegion mask = QRegion(path.toFillPolygon().toPolygon());
    setMask(mask);

    ui->messagePTE->setPlainText(text);
    ui->DTLabel->setText(date);

}

MessageWidget::~MessageWidget()
{
    delete ui;
}
