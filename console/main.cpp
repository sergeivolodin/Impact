#include <iostream>
#include "impact.h"
#include <sstream>
#include <math.h>

using std::cout;
using std::cerr;
using std::stringstream;
using std::endl;

number_t pow_(number_t a, number_t b)
{
    if(a > 0) return(pow(a, b));
    else return(-pow(-a, b));
}

f_result p(number_t x, number_t y)
{
    f_result res;
    res.z = (x * x + y * y) / 10. + 1;
    res.color = vect(fabs(sin(x)*sin(x)), fabs(cos(y)), fabs(sin(res.z)));

    return(res);
}

float a = 100, b = 20, c = 0.1;

f_result plane(number_t x, number_t y)
{
    f_result res;
    res.z = 0;
    res.color = vect(c, c, c);
    return(res);
}

f_result plane_up(number_t x, number_t y)
{
    f_result res;
    res.z = 50;
    res.color = vect(c, c, c);
    return(res);
}

f_result b1(number_t x, number_t y)
{
    f_result res;
    res.z = a * (x + b);
    res.color = vect(c, c, c);
    return(res);
}

f_result b2(number_t x, number_t y)
{
    f_result res;
    res.z = -a * (x - b);
    res.color = vect(c, c, c);
    return(res);
}

f_result b3(number_t x, number_t y)
{
    f_result res;
    res.z = a * (y + b);
    res.color = vect(c, c, c);
    return(res);
}

f_result b4(number_t x, number_t y)
{
    f_result res;
    res.z = -a * (y - b);
    res.color = vect(c, c, c);
    return(res);
}

f_result sin_cos(number_t x, number_t y)
{
    f_result res;
    //res.z = (pow(x, 2) + pow(y, 2)) / 100;
    res.z = 3 * sin(x) + cos(y);
    //res.z = 0;
    res.color = vect(fabs(sin(x) * sin(x)) * 0.5, fabs(cos(y)) * 0.3, fabs(sin(res.z)) * 0.3);
    return(res);
}

number_t dt = 0;

number_t one()
{
    Impact w;

    w.set_gravity(vect(0, 0, 0));
    w.set_dt(dt);
    w.set_use_gravity_n2(false);

    w.add_function(plane);
    w.add_function(plane_up);
    w.add_function(b1);
    w.add_function(b2);
    w.add_function(b3);
    w.add_function(b4);

    w.add_gravity_point(vect(0, 70, 0), 10);
    w.add_gravity_point(vect(0, -20, 0), 10);

    w.add_points(p, 15, 0.5, vect(0, 0, 0), 1);

    number_t wait = 200;

    for(w.set_dt(dt); w.get_simulation_time() + dt < wait; w.physics(dt));
    w.physics(wait - w.get_simulation_time());


    for(w.set_dt(-dt); w.get_simulation_time() - dt > 0; w.physics(-dt));
    w.physics(-w.get_simulation_time());

    unsigned long long int i;
    point t_point;

    number_t velocity_diff = 0, position_diff = 0;

    for(i = 0; i < w.get_points_N(); i++)
    {
        t_point = w.get_difference_default(i);

        velocity_diff += t_point.velocity.abs();
        position_diff += t_point.position.abs();
    }

    //cout << "vel.: " << velocity_diff / w.get_points_N() << endl;
    //cout << "pos.: " << position_diff / w.get_points_N() << endl;
    return(position_diff / w.get_points_N());
}

int main()
{
    dt = 1;
    cerr << one();
    cout.precision(10);
    number_t t_num;
    for(dt = 0.01; dt < 10; dt += 0.01)
    {
        t_num = one();
        cout << dt << ", " << t_num << endl;
    }
    return(0);
}
