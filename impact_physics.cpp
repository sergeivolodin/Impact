#include "impact.h"
#include "vect.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

using std::cout;
using std::pair;
using std::endl;

void Impact::physics_impact(unsigned int f, point& p_old, point& p_new, number_t dtime)
{
    static number_vect_t time_l, time_m, time_r;
    static number_t t1, t2;
    static unsigned int t_count;
    static vect n;

    int old_state = p_old.states[f],
        new_state = difference(p_new.position, myfunctions[f]);

    if(new_state != old_state && new_state != DIFFERENCE_NAN && old_state != DIFFERENCE_NAN)
    {
        t1 = ((f_result (*)(number_t, number_t))(myfunctions[f].first))(p_old.position.x, p_old.position.z).coordinates.z;
        t2 = ((f_result (*)(number_t, number_t))(myfunctions[f].first))(p_new.position.x, p_new.position.z).coordinates.z;

        if(t1 == t1 && t2 == t2)
        {
            if(precise_impact)
            {
                time_l = fmin(0, dtime);
                time_r = fmax(0, dtime);
                time_m = (time_l + time_r) / 2;
                t_count = 0;
                while((time_m - time_l > 0) && (time_r - time_m > 0)
                      && (impact_max_iterations == 0 || t_count < impact_max_iterations))
                {
                    t_count++;
                    p_new.position = p_old.position;
                    p_new.velocity = p_old.velocity;
                    physics_move(p_new, time_m);

                    if((difference(p_new.position, myfunctions[f]) == old_state) ^ (dtime < 0))
                        time_l = time_m;
                    else time_r = time_m;

                    time_m = (time_l + time_r) / 2;
                }

                p_new.position = p_old.position;
                p_new.velocity = p_old.velocity;
                physics_move(p_new, time_m);
            }

            n = tangent(myfunctions[f], p_new.position.x, p_new.position.z);
            p_new.velocity = impact(n, p_new.velocity);

            if(precise_impact)
            {
                if(dtime > 0 && dtime > time_m) physics_move(p_new, dtime - time_m);
                else if(dtime < 0 && dtime < time_m) physics_move(p_new, -fabs(dtime - time_m));
            }
        }
    }
    else if(old_state == DIFFERENCE_NAN && new_state != DIFFERENCE_NAN) p_new.states[f] = new_state;
    else if(new_state == DIFFERENCE_NAN) p_new.states[f] = DIFFERENCE_NAN;
}

void Impact::physics(number_t dtime)
{
    if(track_path) save_points();

    vector<point>::iterator it;
    unsigned int f;
    static point p_old;

    for(it = mypoints.begin(); it != mypoints.end(); it++)
        physics_set_acceleration(*it);

    for(it = mypoints.begin(); it != mypoints.end(); it++)
    {
        p_old = *it;
        physics_move(*it, dtime);

        for(f = 0; f < myfunctions.size(); f++)
            if(myfunctions[f].second.type == function_info::T_COORDINATE
             && fabs((*it).position.x) <= M && fabs((*it).position.z) < M)
                physics_impact(f, p_old, *it, dtime);
            else (*it).states[f] = DIFFERENCE_NAN;
    }
    time += dtime;
}

void Impact::physics_move(point& pt, number_t dtime)
{
    pt.position += (pt.velocity * dtime) + (pt.acceleration * (dtime * dtime / 2.));
    pt.velocity += pt.acceleration * dtime;

    pt.angular_velocity += pt.angular_acceleration * dtime;
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
