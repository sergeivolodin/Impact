#include <QtGui/QApplication>
#include "draw.h"
#include <vect.h>
#include <math.h>
#include <iostream>

using std::endl;
using std::cout;
using std::cerr;

float eps = 1E-2;

number_t f1_a(number_t x, number_t y)
{
    //x = x / 10.;
    number_t r = sqrt(x * x + y * y);
    r = 1 / r;
    //return(static_cast<number_t>( ~ static_cast<long long int>(x) | static_cast<long long int>(y)));
    return(r);
}

f_result f1(number_t x, number_t y)
{
    f_result res;

    res.z = f1_a(x, y);

    res.color = vect(1, 1, 1);
    float d_x = (res.z - f1_a(x + eps, y)) / eps, d_y = (res.z - f1_a(x, y + eps)) / eps;
    res.color.z = sqrt(pow(d_x, 2) + pow(d_y, 2)) * 4;
    res.color.y = fabs(d_x);
    res.color.x = fabs(d_y);
    /*res.color.x = (sin(res.z * 5) + 1.9) / 9;
    res.color.y = (cos(res.z * 5) + 1.9) / 9;
    res.color.z = (cos(res.z * 5) + 1) / 9;*/

    return(res);
}

f_result p(number_t x, number_t y)
{
    f_result res;

    res.z = pow(x, 6) + pow(y, 6) + 10;

    res.color = vect(1, 1, 1);
    res.color.x = (sin(res.z / 5) + 1.7) / 2.7;
    res.color.y = (cos(res.z / 5) + 1.5) / 2.5;
    res.color.z = (cos(res.z / 5) + 1) / 2;

    return(res);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Draw w;

    w.set_gravity(vect(0, -0.1, 0));
    w.set_dt(0.1);
    w.set_dt_for_views(1);
    w.set_use_gravity_n2(false);

    w.add_function(f1);
    w.add_points(p, 1, 0.01, vect(0, 0, 0), 1);

    w.ftl();

    w.show();


    return a.exec();
}

