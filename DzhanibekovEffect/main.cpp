#include <QtGui/QApplication>
#include "draw.h"
#include <vect.h>
#include <math.h>

number_t a = 2, b = 10, c = 10;

f_result ellipsoid0(number_t x, number_t y)
{
    f_result res;
    res.color = vect(1, 1, 1);
    res.coordinates.z = c * sqrt(1 - pow(x / a, 2) - pow(y / b, 2));
    return(res);
}

f_result ellipsoid1(number_t x, number_t y)
{
    f_result res = ellipsoid0(x, y);
    res.coordinates.z = -res.coordinates.z;
    return(res);
}

f_result pellipsoid(number_t x, number_t y)
{
    f_result res;
    res.color = vect(1, 1, 1);
    res.coordinates.x = a * cos(x) * cos(y);
    res.coordinates.y = b * cos(x) * sin(y);
    res.coordinates.z = c * sin(x);
    return(res);
}

f_result fplane(number_t x, number_t y)
{
    f_result res;
    res.color = vect(0.8, 0, 0);
    res.coordinates.z = 0;
    return(res);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Draw w;

    function plane, e1, e2;
//    e1.first = (void*) ellipsoid0;
//    e2.first = (void*) ellipsoid1;

    plane.first = (void*) fplane;
    e1.first = (void*) pellipsoid;

    plane.second.type = function_info::T_COORDINATE;
    plane.second.xmin = -20;
    plane.second.xmax = 20;
    plane.second.xstep = 0.1;
    plane.second.ymin = -20;
    plane.second.ymax = 20;
    plane.second.ystep = 0.1;

    e1.second = plane.second;
    e1.second.type = function_info::T_PARAMETRIC;
    e1.second.xmin = -M_PI / 2;
    e1.second.xmax =  M_PI / 2;
    e1.second.ymin = -M_PI;
    e1.second.ymax =  M_PI;


    w.add_function(e1);
    w.add_function(plane);
    //w.add_function(e2);

    w.ftl();
    w.show();
    return a.exec();
}
