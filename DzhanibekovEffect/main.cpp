#include <QtGui/QApplication>
#include "draw.h"
#include <vect.h>
#include <math.h>
#include <iostream>

using std::cout;
using std::endl;

number_t a = 3, b = 5, c = 7, r = 4;

f_result ellipsoid(number_t x, number_t y)
{
    f_result res;
    res.color = vect(0, 0.1, 0);
    res.coordinates.x = a * cos(x) * cos(y);
    res.coordinates.y = b * cos(x) * sin(y);
    res.coordinates.z = c * sin(x);
    return(res);
}

f_result sphere(number_t x, number_t y)
{
    f_result res;
    res.color = vect(0.3, 0, 0);
    res.coordinates.x = r * cos(x) * cos(y);
    res.coordinates.y = r * cos(x) * sin(y);
    res.coordinates.z = r * sin(x);
    return(res);
}

f_result curve1(number_t x, number_t y)
{
    f_result res;
    res.color = vect(1, 1, 1);

    //number_t t = (pow(r, 2) - pow(a * cos(x), 2) - pow(c * sin(x), 2)) / (pow(cos(x), 2) * (pow(b, 2) - pow(a, 2)));
    //y = asin(sqrt(t));

    number_t t = (pow(r, 2) - pow(c, 2)) / (pow(a * cos(y), 2) + pow(b * sin(y), 2) - pow(c, 2));
    x = acos(sqrt(t));

    res.coordinates.x = a * cos(x) * cos(y);
    res.coordinates.y = b * cos(x) * sin(y);
    res.coordinates.z = c * sin(x);
    return(res);
}

f_result curve2(number_t x, number_t y)
{
    f_result res = curve1(x, y);
    res.coordinates.z *= -1;
    return(res);
}

f_result plane(number_t x, number_t y)
{
    f_result res;
    res.color = vect(0, 0, 0.1);
    res.coordinates.z = 0;
    return(res);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Draw w;

    function p, e, s, c1, c2;

    p.first = (void*) plane;
    e.first = (void*) ellipsoid;
    s.first = (void*) sphere;
    c1.first = (void*) curve1;
    c2.first = (void*) curve2;

    p.second.type = function_info::T_COORDINATE;
    p.second.xmin = -20;
    p.second.xmax = 20;
    p.second.xstep = 0.1;
    p.second.ymin = -20;
    p.second.ymax = 20;
    p.second.ystep = 0.1;

    e.second = p.second;
    e.second.type = function_info::T_PARAMETRIC;
    e.second.xmin = -M_PI / 2;
    e.second.xmax =  M_PI / 2;
    e.second.ymin = -M_PI;
    e.second.ymax =  M_PI;

    s.second = e.second;
    c1.second = e.second;
    c1.second.xmin = 0;
    c1.second.xmax = 0;
    c1.second.xstep = 1;
    c1.second.ymin = 0;
    c1.second.ymax = 10 * M_PI;
    c1.second.ystep = 2 * M_PI / 1000;
    c2.second = c1.second;



    //w.add_function(p);
    w.add_function(e);
    //w.add_function(s);
    w.add_function(c1);
    w.add_function(c2);

    w.ftl();
    w.show();
    return a.exec();
}
