#include "impact.h"
#include "vect.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using std::cout;
using std::pair;
using std::endl;

void Impact::physics(number_t dtime)
{
    if(track_path) save_points();

    for(int i = 0; i < mypoints.size(); i++)
    {
        physics_move(i, dtime);
    }
    time += dtime;
}

void Impact::physics_move(int i, number_t dtime)
{
    point& pt = mypoints[i];
    if(i > 0)
    {
        pt.position.x     = cos(omega * time);
        pt.position.y     = sin(omega * time);
        pt.velocity.x     = -omega * sin(omega * time);
        pt.velocity.y     =  omega * cos(omega * time);
        pt.acceleration.x = -omega * omega * cos(omega * time);
        pt.acceleration.y = -omega * omega * sin(omega * time);

        pt.position.z = 1;

        double Theta, Omega = -omega;


        if(i >= 2);
            Theta = M_PI / 10 * (i - 2);

        if(i >= 2)
        {
            pt.position.x     += cos(Omega * time + Theta);
            pt.position.y     += sin(Omega * time + Theta);
            pt.velocity.x     += -Omega * sin(Omega * time + Theta);
            pt.velocity.y     +=  Omega * cos(Omega * time + Theta);
            pt.acceleration.x += -Omega * Omega * cos(Omega * time + Theta);
            pt.acceleration.y += -Omega * Omega * sin(Omega * time + Theta);
        }
    }
}

void Impact::physics_set_acceleration(point& pt)
{
    pt.acceleration = vect(0, 0, 0);
    pt.angular_acceleration = vect(0, 0, 0);

    pair<vect, vect> t_pair1;
    if(use_gravity) pt.acceleration += gravity;

    vector<point>::iterator it;
    if(use_gravity_n2)
        for(it = mypoints.begin(); it != mypoints.end(); it++)
            pt.acceleration += physics_gravity(pt, *it);
    if(use_gravitomagnetism_force || use_gravitomagnetism_torque)
        for(it = mypoints.begin(); it != mypoints.end(); it++)
        {
            t_pair1 = physics_gravitomagnetism(pt, *it);
            pt.acceleration += t_pair1.first;
            pt.angular_acceleration += t_pair1.second;
        }
}

vect Impact::physics_gravity(point& p1, point& p2)
{
    vect t_position = p2.position;
    vect acc1(0, 0, 0);
    t_position -= p1.position;
    if(fabs(t_position.abs_2()) > 1)
        acc1 = (t_position * (p2.mass / pow(fabs(t_position.abs()), 3))) * G;
    return(acc1);
}

pair<vect, vect> Impact::physics_gravitomagnetism(point &p1, point &p2)
{
    pair<vect, vect> res;
    res.first = vect(0, 0, 0);
    res.second = vect(0, 0, 0);
    if(p2.angular_velocity.abs() == 0) return(res);
    vect r = p1.position - p2.position;
    if(r.abs() == 0)
        return(res);
    vect r_norm = r / r.abs();
    vect L = p2.angular_velocity * p2.moment_of_inertia;
    vect Bg = (L - r_norm * (3 * (L * r_norm))) * G / (2 * pow(c, 2) * pow(r.abs(), 3));

    if(use_gravitomagnetism_force) res.first = (p1.velocity ^ Bg);
    if(use_gravitomagnetism_torque) res.second = (p1.angular_velocity ^ Bg) * 0.5;

    return(res);
}
