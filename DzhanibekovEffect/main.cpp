#include <QtGui/QApplication>
#include "draw.h"
#include <vect.h>
#include <math.h>

number_t a = 10, b = 20, c = 30;

f_result ellipsoid0(number_t x, number_t y)
{
    f_result res;
    res.color = vect(1, 1, 1);
    res.z = c * sqrt(1 - pow(x / a, 2) - pow(y / b, 2));
    return(res);
}

f_result ellipsoid1(number_t x, number_t y)
{
    f_result res = ellipsoid0(x, y);
    res.z = -res.z;
    return(res);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Draw w;

    w.add_function(ellipsoid0);
    w.add_function(ellipsoid1);

    w.ftl();
    w.show();
    return a.exec();
}
