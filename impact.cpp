#include "impact.h"
#include "vect.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using std::cerr;
using std::endl;
using std::cout;

Impact::Impact()
{
    G = 1;
    c = 10000;
    derivative_eps = 1e-2;
    use_gravity_points = true;
    use_gravity = true;
    use_gravitomagnetism_force = false;
    use_gravitomagnetism_torque = false;
    track_path = false;
    use_gravity_n2 = false;
    time = 0;
    M = 60;
    dt = 0.1;
}

number_t Impact::get_simulation_time()
{
    return(time);
}

void Impact::add_points(f_result(*f)(number_t, number_t), number_t M, number_t step, vect velocity, number_t mass, vect angular_velocity, number_t moment_of_inertia)
{
    number_t x, z;

    vect new_position;
    f_result t_res;

    for(x = -M; x <= M; x += step)
    {
        for(z = -M; z <= M; z += step)
        {
            t_res = f(x, z);
            new_position = vect(x, t_res.z, z);
            add_point(new_position, velocity, t_res.color, mass, angular_velocity, moment_of_inertia);
        }
    }
}

void Impact::add_function(f_result(*f)(number_t, number_t))
{
    myfunctions.push_back(f);
    vector<point>::iterator it;
    vector<bool> a;
    for(it = mypoints.begin(); it != mypoints.end(); it++)
    {
        (*it).states.resize((*it).states.size() + 1);
        (*it).states[(*it).states.size() - 1] = difference((*it).position, f);
    }
}

void Impact::add_gravity_point(vect position, number_t mass)
{
    point t_point;
    t_point.mass = mass;
    t_point.position = position;
    mygravitypoints.push_back(t_point);
}

void Impact::add_point(vect position, vect velocity, vect color, number_t mass, vect angular_velocity, number_t moment_of_inertia)
{
    point a;
    a.color = color;
    a.states.reserve(myfunctions.size());
    a.position = position;
    a.acceleration = vect(0, 0, 0);
    a.velocity = velocity;
    a.mass = mass;
    a.angular_acceleration = vect(0, 0, 0);
    a.angular_velocity = angular_velocity;
    a.moment_of_inertia = moment_of_inertia;

    vector<f_result (*)(number_t, number_t)>::iterator it;
    for(it = myfunctions.begin(); it != myfunctions.end(); it++)
    {
        a.states.push_back(difference(position, (*it)));
    }

    mypoints.push_back(a);
    mypoints_defaults.push_back(a);
}

void Impact::set_gravity(vect x)
{
    gravity = x;
}

void Impact::set_dt(number_t x)
{
    dt = x;
}

void Impact::set_use_gravity_n2(bool x)
{
    use_gravity_n2 = x;
}

void Impact::set_use_gravitomagnetism_force(bool x)
{
    use_gravitomagnetism_force = x;
}

void Impact::set_use_gravitomagnetism_torque(bool x)
{
    use_gravitomagnetism_torque = x;
}

number_t Impact::derivative_x(f_result(*f)(number_t, number_t), number_t x, number_t y)
{
    return((f(x + derivative_eps, y).z - f(x, y).z) / derivative_eps);
}

number_t Impact::derivative_y(f_result(*f)(number_t, number_t), number_t x, number_t y)
{
    return((f(x, y + derivative_eps).z - f(x, y).z) / derivative_eps);
}

vect Impact::tangent(f_result(*f)(number_t, number_t), number_t x, number_t y)
{
    vect result;
    result.x = derivative_x(f, x, y);
    result.z = derivative_y(f, x, y);
    result.y = -1;
    return(result);
}

int Impact::difference(vect coords, f_result(*f)(number_t, number_t))
{
    number_t a = f(coords.x, coords.z).z;

    if(a != a) return(DIFFERENCE_NAN);

    number_t b = coords.y;
    if(a > b) return(1);
    if(a < b) return(-1);
    return(0);
}

/*number_t tan_plane(number_t x, number_t y)
{
    number_t x0 = point_->position.x, y0 = point_->position.z;
    vect normal = tangent(func, x0, y0);
    number_t z = func(x0, y0) + normal.x * (x - x0) + normal.z * (y - y0);
    return(z);
}*/

point Impact::get_difference_default(unsigned long long int pt)
{
    if(mypoints.size() <= pt) return(point());
    point res = mypoints_defaults[pt];

    res.acceleration -= mypoints[pt].acceleration;
    res.velocity -= mypoints[pt].velocity;
    res.position -= mypoints[pt].position;

    return(res);
}

unsigned long long Impact::get_points_N()
{
    return(mypoints.size());
}

void Impact::firework(vect position, number_t velocity, number_t mass, vect angular_velocity, number_t moment_of_inertia, unsigned int N)
{
    vect t_velocity, t_angle, t_color(1, 1, 1);
    number_t x, y, z;
    while(N--)
    {
        x = (2 * rand() - RAND_MAX) * 2 * M_PI / RAND_MAX;
        y = (2 * rand() - RAND_MAX) * 2 * M_PI / RAND_MAX;
        z = (2 * rand() - RAND_MAX) * 2 * M_PI / RAND_MAX;

        t_velocity = vect(0, 0, 0);
        t_color = vect(fabs(sin(x)), fabs(sin(y)), fabs(sin(z)));
        t_angle = vect(x, y, z);
        forward(velocity, &t_velocity, &t_angle);
        add_point(position, t_velocity, t_color, mass, angular_velocity, moment_of_inertia);
    }
}

vect Impact::get_color(vect velocity)
{
    vect res(fabs(sin(velocity.x * 2)), fabs(sin(velocity.y * 2)), fabs(sin(velocity.z * 2)));
    return(res);
}

