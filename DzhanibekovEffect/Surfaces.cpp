#include "Surfaces.h"

f_result ellipsoid(number_t x, number_t y)
{
    f_result res;
    res.color = vect(1, 1, 1);
    res.coordinates.x = a * cos(x) * cos(y);
    res.coordinates.y = b * cos(x) * sin(y);
    res.coordinates.z = c * sin(x);
    return(res);
}

f_result sphere(number_t x, number_t y, void* r)
{
    f_result res;
    res.color = vect(0.3, 0, 0);
    res.coordinates.x = (*(number_t *)r) * cos(x) * cos(y);
    res.coordinates.y = (*(number_t *)r) * cos(x) * sin(y);
    res.coordinates.z = (*(number_t *)r) * sin(x);
    return(res);
}

f_result curve1(number_t x, number_t y, void *g)
{
    f_result res;

    curve_param p = *((curve_param *)g);
    res.color = p.color;

    number_t r = p.r;

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

f_result curve2(number_t x, number_t y, void *g)
{
    f_result res = curve1(x, y, g);
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
