#include <QApplication>
#include "DEG.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DEG w;
    w.show();
    
    return a.exec();
}
