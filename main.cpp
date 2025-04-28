#include "randomselector.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RandomSelector w;
    w.show();
    return a.exec();
}
