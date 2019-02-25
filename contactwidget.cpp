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
    ui->nameLabel->setText(sl[0]);

    QFont font("URW Chancery L", 20);
    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect();
    effect->setOffset(2);


    QString thumbnail = QString(sl[0][0]) + QString(sl[1][0]);
    ui->thumbnailLabel->setAlignment(Qt::AlignCenter);
    ui->thumbnailLabel->setText(thumbnail);
    ui->thumbnailLabel->setFont(font);
    ui->thumbnailLabel->setGraphicsEffect(effect);
    //ui->nameLabel->setFont(font);
    //ui->nameLabel->setGraphicsEffect(effect);

    setToolTip(name);


    /*const int radius = 10;
    QPainterPath path;
    path.addRoundedRect(rect(), radius, radius);
    QRegion mask = QRegion(path.toFillPolygon().toPolygon());
    setMask(mask);*/
    //widget->setMask(mask);

    //widget->show();
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
