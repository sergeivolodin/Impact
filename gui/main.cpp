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
    number_t res = -(x * x + y * y);
    return(res / 50.);
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
    res.color.z = sqrt(pow(d_x, 2) + pow(d_y, 2)) / 10;
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

    res.z = x * x + y * y + 5;

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
    w.set_dt(0.05);
    w.set_dt_for_views(1);
    w.set_use_gravity_n2(false);
    w.set_use_gravitomagnetism_force(false);
    w.set_use_gravitomagnetism_torque(false);

    w.add_function(f1);
    //w.add_function(f2);
    //w.add_function(plane);
    w.add_points(p, 0.3, 0.1, vect(0, -1, 0), 1, vect(0, 0, 0), 0);
    //w.add_point(vect(0, 10, 0), vect(0, 0, 0), vect(1, 1, 1), 10, vect(0, 10, 0));
    //w.add_point(vect(0, 10, 0), vect(0.1, 0, 0), vect(0, 1, 0), 10, vect(1111, 1111, 0));
    //w.add_point(vect(50, 20, 0), vect(0, 0, 0), vect(1, 1, 0), -10, vect(10, 0, 0), 1E10);
    //w.add_point(vect(-50, 20, 10), vect(0, 0, 0), vect(1, 1, 0), 10, vect(0, 10, 0), 1E10);
    //w.firework(vect(0, 30, 0), 0.1, 1, vect(0, 0, 0), 0, 100);

    //for(float t = 0; t < 2 * M_PI; t += M_PI / 10)
        //w.add_point(vect(sin(t) * 100, 0, cos(t) * 100), vect(0.1, 0.3, 0.1), vect(1, 0, 1), 1, vect(t, 10, t), 1E8);

    w.ftl();

    w.show();


    return a.exec();
}

