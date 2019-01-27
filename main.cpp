#include "telegraphwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TelegraphWindow w;
    w.show();

    return a.exec();
}
