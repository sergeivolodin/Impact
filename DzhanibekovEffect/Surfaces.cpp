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

f_result ellipsoidVisible(number_t x, number_t y, void* r0)
{
    vect r = *((vect*) r0);
    vect r1, e11, e21, e31;
    vect R11, R1, R;

    r1.x =  -r.x;
    r1.y =  -r.y;
    r1.z =  -r.z;

    //affine transformation
    r1.x = r1.x / a;
    r1.y = r1.y / b;
    r1.z = r1.z / c;

    //new basis
    e11 = r1 / r1.abs();
    e21 = e11 ^ vect(0, 0, 1);

    if(e21.abs() == 0)
        e21 = e11 ^ vect(0, 1, 0);

    e21 = e21 / e21.abs();

    e31 = e11 ^ e21;

    //equation in the new basis e11e21e31
    R11.x = 1 / r1.abs();
    R11.y = sqrt(r1.abs_2() - 1) / r1.abs() * cos(x);
    R11.z = sqrt(r1.abs_2() - 1) / r1.abs() * sin(x);

    //affine image of line
    R1.x = e11.x * R11.x + e21.x * R11.y + e31.x * R11.z;
    R1.y = e11.y * R11.x + e21.y * R11.y + e31.y * R11.z;
    R1.z = e11.z * R11.x + e21.z * R11.y + e31.z * R11.z;

    //backwards affine transformation
    R.x = R1.x * a;
    R.y = R1.y * b;
    R.z = R1.z * c;

    f_result res;
    res.color = vect(1, 0, 0);
    res.coordinates = R;
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
