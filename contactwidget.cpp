#include "contactwidget.h"
#include "ui_contactwidget.h"
#include <QGraphicsDropShadowEffect>
#include <QFont>
#include <QPainterPath>
#include <QRegion>

ContactWidget::ContactWidget(QString name, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContactWidget)
{
    QStringList sl = name.split('_');

    ui->setupUi(this);
    ui->nameLabel->setText(/*sl[0]*/name);

    QFont font("URW Chancery L", 20);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setOffset(2);


    QString thumbnail = QString(sl[0][0]) + QString(sl[1][0]);
    ui->thumbnailLabel->setAlignment(Qt::AlignCenter);
    ui->thumbnailLabel->setText(thumbnail);
    ui->thumbnailLabel->setFont(font);
    ui->thumbnailLabel->setGraphicsEffect(effect);

    setToolTip(name);
}

ContactWidget::~ContactWidget()
{
    delete ui;
}

void ContactWidget::enableAddPB(bool enable)
{
    ui->addPB->setVisible(enable);
}

void ContactWidget::on_addPB_clicked()
{
    emit add(ui->nameLabel->text());
    ui->addPB->setVisible(false);
}
