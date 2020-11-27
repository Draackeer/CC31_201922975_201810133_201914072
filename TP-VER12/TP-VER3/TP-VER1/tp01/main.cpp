#include "daleplay.h"


#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DalePlay w;
    w.show();
    return a.exec();
}
