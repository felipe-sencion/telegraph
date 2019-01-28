#include "telegraph.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Telegraph telegrapgh;
    telegrapgh.start();

    return a.exec();
}
