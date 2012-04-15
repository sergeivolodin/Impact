#include <QtGui/QApplication>
#include "impact.h"
#include <vect.h>
#include <math.h>
#include <iostream>

using std::endl;
using std::cout;
using std::cerr;

number_t pow_(number_t a, number_t b)
{
    if(a > 0) return(pow(a, b));
    else return(-pow(-a, b));
}

f_result f2(number_t x, number_t y)
{
    f_result res;
    res.z = (x * x + y * y) / 50 + 5;
    res.color = vect(fabs(sin(x)*sin(x)), fabs(cos(y)), fabs(sin(res.z)));

    return(res);
}

f_result f3(number_t x, number_t y)
{
    f_result res;
    res.z = 20;
    res.color = vect(0.3, 0.3, 0.3);
    return(res);
}

f_result f1(number_t x, number_t y)
{
    f_result res;
    res.z = 0;
    res.color = vect(0.3, 0.3, 0.3);
    return(res);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Impact w;

    w.set_gravity(0, -0.1, 0);
    w.set_dt(0.25);

    w.add_function(f1);
    w.add_function(f3);
    w.add_points(f2, 15., 0.09, vect(0, -2, 0));
    w.ftl();

    w.show();

    return a.exec();
}

