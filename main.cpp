#include "geninvent.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GenInvent w;
    w.show();
    return a.exec();
}
