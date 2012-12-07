#include <QtGui/QApplication>
#include "draw.h"
#include <vect.h>
#include <math.h>

number_t a = 3, b = 5, c = 7, r = 4;

f_result ellipsoid(number_t x, number_t y)
{
    f_result res;
    res.color = vect(0, 0.7, 0);
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

f_result curve(number_t x, number_t y)
{
    f_result res;
    res.color = vect(0.3, 0, 0);
    res.coordinates.x = sin(x);
    res.coordinates.y = cos(x);
    res.coordinates.z = x;
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

    function p, e, s, c;

    p.first = (void*) plane;
    e.first = (void*) ellipsoid;
    s.first = (void*) sphere;
    c.first = (void*) curve;

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
    c.second = e.second;
    c.second.xmin = -50;
    c.second.xmax = 50;
    c.second.xstep = 0.1;
    c.second.ymin = 0;
    c.second.ymax = 0;
    c.second.ystep = 1;

    w.add_function(p);
    //w.add_function(e);
    //w.add_function(s);
    w.add_function(c);

    w.ftl();
    w.show();
    return a.exec();
}
