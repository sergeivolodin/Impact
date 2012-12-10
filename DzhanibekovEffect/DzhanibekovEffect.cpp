#include "DzhanibekovEffect.h"
#include <iostream>

using std::cout;
using std::endl;

f_result DzhanibekovEffect::ellipsoid(number_t x, number_t y)
{
    f_result res;
    res.color = vect(0, 0.1, 0);
    res.coordinates.x = a * cos(x) * cos(y);
    res.coordinates.y = b * cos(x) * sin(y);
    res.coordinates.z = c * sin(x);
    return(res);
}

f_result DzhanibekovEffect::sphere(number_t x, number_t y)
{
    f_result res;
    res.color = vect(0.3, 0, 0);
    res.coordinates.x = r * cos(x) * cos(y);
    res.coordinates.y = r * cos(x) * sin(y);
    res.coordinates.z = r * sin(x);
    return(res);
}

f_result DzhanibekovEffect::curve1(number_t x, number_t y)
{
    f_result res;
    res.color = vect(1, 1, 1);

    //number_t t = (pow(r, 2) - pow(a * cos(x), 2) - pow(c * sin(x), 2)) / (pow(cos(x), 2) * (pow(b, 2) - pow(a, 2)));
    //y = asin(sqrt(t));

    number_t t = (pow(r, 2) - pow(c, 2)) / (pow(a * cos(y), 2) + pow(b * sin(y), 2) - pow(c, 2)), t1;
    x = acos(sqrt(t));

    if(x != x)
    {
        t1 = fabs(acos(sqrt((pow(r, 2) - pow(b, 2)) / (pow(a, 2) - pow(b, 2)))));

        if(y > 0 && y < M_PI / 2)
        {
            y = t1;
            x = 0;
        }
        /*else if(y > M_PI / 2 && y < M_PI)
        {
            y = -t1;
            x = M_PI;
        }*/
        else if(y > M_PI && y < 3 * M_PI / 2)
        {
            y = t1;
            x = M_PI;
        }
        else if(y > 3 * M_PI / 2 && y < 2 * M_PI)
        {
//            y = -(M_PI + t1);
//            x = 0;
        }
    }

    res.coordinates.x = a * cos(x) * cos(y);
    res.coordinates.y = b * cos(x) * sin(y);
    res.coordinates.z = c * sin(x);
    return(res);
}

f_result DzhanibekovEffect::curve2(number_t x, number_t y)
{
    f_result res = curve1(x, y);
    res.coordinates.z *= -1;
    return(res);
}

f_result DzhanibekovEffect::plane(number_t x, number_t y)
{
    f_result res;
    res.color = vect(0, 0, 0.1);
    res.coordinates.z = 0;
    return(res);
}

DzhanibekovEffect::DzhanibekovEffect()
{
    function p, e, s, c1, c2;

    p.first = (void*) plane;
    e.first = (void*) ellipsoid;
    s.first = (void*) sphere;
    c1.first = (void*) curve1;
    c2.first = (void*) curve2;

    p.second.type = function_info::T_COORDINATE;
    p.second.xmin = -20;
    p.second.xmax = 20;
    p.second.xstep = 0.05;
    p.second.ymin = -20;
    p.second.ymax = 20;
    p.second.ystep = 0.05;

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
    c1.second.ystep = 2 * M_PI / 10000;
    c2.second = c1.second;



    //add_function(p);
    add_function(e);
    add_function(s);
    add_function(c1);
    add_function(c2);
}
