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
    x = x / 5;
    y = y / 5;
    number_t r = sqrt(x * x + y * y);
    /*r = 1 / r;
    //return(static_cast<number_t>( ~ static_cast<long long int>(x) | static_cast<long long int>(y)));*/
    number_t x1 = log(3 - r) / log(12 * r * r - 41 * r + 35);
    number_t x2 = log(3 - r) / log(2 * r * r - 5 * r + 3);
    //number_t x3 = log(5 - r) / log(2 * r * r - 5 * r + 10);

    number_t res;

    if(r >= 0.3)
        res = r * r;
    else res = log(-1);

    //number_t res = pow(3, 0.5) / 2 * (pow(r, 2) - 16) / (r + 8);

    //if(res != res) res = 0;
    //if(res > 100) res = 100;
    //else if(res < -100) res = -100;

    return(res);
}

f_result plane(number_t x, number_t y)
{
    f_result res;

    res.z = 0;
    res.color = vect(0.3, 0.3, 0.3);

    return(res);
}

f_result f2(number_t x, number_t y)
{
    f_result res;

    res.z = -f1_a(x, y) + 150;

    res.color = vect(1, 0.1, 0.3);
    float d_x = (res.z + f1_a(x + eps, y) - 150) / eps, d_y = (res.z + f1_a(x, y + eps) - 150) / eps;
    res.color.z = sqrt(pow(d_x, 2) + pow(d_y, 2)) / 100;
    res.color.y = fabs(d_x) / 100;
    res.color.x = fabs(d_y) / 10;
    /*res.color.x = (sin(res.z * 5) + 1.9) / 9;
    res.color.y = (cos(res.z * 5) + 1.9) / 9;
    res.color.z = (cos(res.z * 5) + 1) / 9;*/

    return(res);
}

f_result f1(number_t x, number_t y)
{
    f_result res;

    res.z = f1_a(x, y);

    res.color = vect(0.5, 1, 0.1);
    float d_x = (res.z - f1_a(x + eps, y)) / eps, d_y = (res.z - f1_a(x, y + eps)) / eps;
    res.color.z = sqrt(pow(d_x, 2) + pow(d_y, 2)) / 100;
    res.color.y = fabs(d_x) / 10;
    res.color.x = fabs(d_y) / 10;
    /*res.color.x = (sin(res.z * 5) + 1.9) / 9;
    res.color.y = (cos(res.z * 5) + 1.9) / 9;
    res.color.z = (cos(res.z * 5) + 1) / 9;*/

    return(res);
}

f_result p(number_t x, number_t y)
{
    f_result res;

    res.z = (x * x + y * y) / 10 + 10;

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

    w.set_gravity(vect(0, -0, 0));
    w.set_dt(0.05);
    w.set_dt_for_views(1);
    w.set_use_gravity_n2(false);
    w.set_use_gravitomagnetism(true);

    //w.add_function(f1);
    //w.add_function(f2);
    w.add_function(plane);
    //w.add_points(p, 15, 0.3, vect(3, -5, 10), 1);
    //w.add_point(vect(0, 10, 0), vect(0, 0, 0), vect(1, 1, 1), 10, vect(0, 10, 0));
    w.add_point(vect(0, 10, 0), vect(0.1, 0, 0), vect(0, 1, 0), 10, vect(0, 1111, 0));
    w.add_point(vect(50, 10, 0), vect(-0.1, 0, 0), vect(1, 1, 0), 10, vect(0, 1111, 0));
    //w.add_point(vect(-10, -10, 30), vect(1, 1, 1), vect(1, 1, 0), 10, vect(0, 0, 0));

    w.ftl();

    w.show();


    return a.exec();
}

