#include <QtGui/QApplication>
#include "DzhanibekovEffect.h"
#include <vect.h>
#include <math.h>
#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DzhanibekovEffect w;

    w.ftl();
    w.show();
    return a.exec();
}
