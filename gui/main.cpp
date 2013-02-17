#include <QtGui/QApplication>
#include "draw.h"
#include <vect.h>
#include <math.h>

const number_t eps = 1E-2;

number_t f1_a(number_t x, number_t y)
{
    number_t res;

    number_t r = sqrt(x * x + y * y) / 10;

    //res = x * y / 100;
    res = 0;

    if(res == res)
    {
        if(res > 100) res = 100;
        else if(res < -100) res = -100;
    }
    return(res);
}

number_t f2_a(number_t x, number_t y)
{
    number_t res;

    //number_t r = (x * x + y * y) / 3;
    number_t r = pow(x, 2) * pow(M_E, y - pow(x, 2));

    return(r);
}

f_result f2(number_t x, number_t y)
{
    f_result res;
    res.coordinates.z = f2_a(x, y);
    res.color = vect(0.5, 1, 0.1);
    float d_x = (res.coordinates.z - f1_a(x + eps, y)) / eps, d_y = (res.coordinates.z - f1_a(x, y + eps)) / eps;
    res.color = Draw::get_color(vect(x - y, x + y, y - x));
    return(res);
}

f_result f0(number_t x, number_t y)
{
    f_result res;
    res.coordinates.z = 5;
    res.color = vect(0.5, 1, 0.1);
    float d_x = (res.coordinates.z - f1_a(x + eps, y)) / eps, d_y = (res.coordinates.z - f1_a(x, y + eps)) / eps;
    /*res.color.coordinates.z = sqrt(pow(d_x, 2) + pow(d_y, 2));
    res.color.y = fabs(d_x) / 100;
    res.color.x = fabs(d_y) / 100;*/
    //res.color = Draw::get_color(vect(x, x - y, y));
    //res.color /= 8;
    return(res);
}

f_result f1(number_t x, number_t y)
{
    f_result res;
    res.coordinates.z = 0;
    res.color = vect(0.1, 0.1, 0.1);
    float d_x = (res.coordinates.z - f1_a(x + eps, y)) / eps, d_y = (res.coordinates.z - f1_a(x, y + eps)) / eps;
    /*res.color.coordinates.z = sqrt(pow(d_x, 2) + pow(d_y, 2));
    res.color.y = fabs(d_x) / 100;
    res.color.x = fabs(d_y) / 100;*/
    //res.color = Draw::get_color(vect(x, x - y, y));
    //res.color /= 8;
    return(res);
}

f_result hyp(number_t x, number_t y)
{
    f_result res;

    number_t a = 1, b = 10;

    //res.coordinates.z = 0.5 * (pow(x / a, 2) - pow(y / b, 2));
    //res.coordinates.z = 0.5 * (pow(x / a, 2) + pow(y / b, 2));
    //res.coordinates.z = pow(pow(x, 2) - pow(y, 2), 0.5);
    res.coordinates.z = 0.5 * (pow(x, 2) - pow(y, 2));

    float d_x = (res.coordinates.z - f1_a(x + eps, y)) / eps, d_y = (res.coordinates.z - f1_a(x, y + eps)) / eps;
    res.color = Draw::get_color(vect(d_x, res.coordinates.z, d_y));

    return(res);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Draw w;

    w.setClearColor(vect(0, 0, 0));

    function h, f11, f01;
    h.second.xmin = -20;
    h.second.xmax = 20;
    h.second.xstep = 0.1;
    h.second.ymin = -20;
    h.second.ymax = 20;
    h.second.ystep = 0.1;
    h.second.type == function_info::T_COORDINATE;

    f11.second = h.second;
    f01.second = h.second;
    h.first = (void*) hyp;
    f11.first = (void*) f1;
    f01.first = (void*) f2;

//    w.add_function(h);
    w.add_function(f01);
//    w.add_function(f01);


    //w.add_function(f1);

    //w.set_gravity(vect(0, -0.5, 0));
    //w.firework(vect(30, 20, 0), 5, 1, vect(0, 0, 0), 1, 100);
//    w.set_use_gravity_n2(true);
//    w.set_use_gravitomagnetism_force(false);
//    w.set_use_gravitomagnetism_torque(false);

//    w.add_point(vect(0, 10, 0), vect(0, 0, 0), vect(1, 1, 1), 1E13, vect(0, 0, 0), 0);
//    w.add_point(vect(30, 5, 0), vect(0, 0, 4.6843837106667205), vect(1, 0, 1), 1E7, vect(0, 0, 0), 0);
//    w.add_point(vect(50, 10, 0), vect(0, 0, 3.6534476867747814), vect(1, 0, 1), 1E7, vect(0, 0, 0), 0);
//    w.add_point(vect(80, 10, 0), vect(0, 0, 3.6534476867747814), vect(1, 0, 1), 1E7, vect(0, 0, 0), 0);
//    w.add_point(vect(70, 20, 0), vect(0, 0, 3.0721710631258894), vect(1, 0, 1), 1E10, vect(0, 0, 0), 0);
//    w.add_point(vect(71, 20, 0), vect(0, 0, 3.0721710631258894 - 0.816935737986777), vect(1, 0, 1), 1, vect(0, 0, 0), 0);

    //w.add_point(vect(-50, 3, -5), vect(1, 0, 0), vect(1, 1, 1), 1E12, vect(0, 0, 0), 1);
    //w.add_point(vect(50, 3, 5), vect(-1, 0, 0), vect(1, 1, 1), 1E12, vect(0, 0, 0), 1);

//    w.set_gravity(vect(0, -0.0, 0));
//    w.set_use_gravity_n2(false);
//    w.set_use_gravitomagnetism_force(true);
//    w.set_use_gravitomagnetism_torque(true);
//    w.add_point(vect(0, 5, 0), vect(0, 0, 0), vect(1, 1, 0), 10, vect(0, 10, 0), 1E29);
//    w.add_point(vect(0, 10, 0), vect(1, 0, 0), vect(1, 1, 0), 10, vect(0, 0, 0), 1);

    /*w.set_gravity(vect(0, -0.5, 0));
    w.set_use_gravity_n2(false);
    w.set_use_gravitomagnetism_force(false);
    w.set_use_gravitomagnetism_torque(false);
    w.add_points(f2, 5, 0.09, vect(0, 0, 0), 1, vect(0, 0, 0), 1);
    w.add_function(f1);*/

    w.ftl();
    w.show();
    return a.exec();
}


