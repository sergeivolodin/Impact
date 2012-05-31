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

    //cout << print_points();
    vector<point>::iterator it;
    unsigned int i2;
    static vect old_position, old_velocity, n, new_velocity;
    static number_vect_t time_l, time_m, time_r;
    static number_t t1, t2;
    static unsigned int t_count;

    for(it = mypoints.begin(); it != mypoints.end(); it++)
        physics_set_acceleration(*it);

    for(it = mypoints.begin(); it != mypoints.end(); it++)
    {
        if(precise_impact)
        {
            old_position = (*it).position;
            old_velocity = (*it).velocity;
        }

        physics_move((*it), dtime);


        if(fabs((*it).position.x) <= M && fabs((*it).position.z) < M)
        {
            for(i2 = 0; i2 < myfunctions.size(); i2++)
            {
                int old_state = (*it).states[i2],
                    new_state = difference((*it).position, myfunctions[i2]);

                if(new_state != old_state && new_state != DIFFERENCE_NAN && old_state != DIFFERENCE_NAN)
                {
                    t1 = myfunctions[i2](old_position.x, old_position.z).z;
                    t2 = myfunctions[i2]((*it).position.x, (*it).position.z).z;

                    if(t1 == t1 && t2 == t2)
                    {

                        if(precise_impact)
                        {
                            time_l = fmin(0, dtime);
                            time_r = fmax(0, dtime);
                            time_m = (time_l + time_r) / 2;
                            t_count = 0;
                            while((time_m - time_l > 0) && (time_r - time_m > 0) && (impact_max_iterations == 0 || t_count < impact_max_iterations))
                            {
                                t_count++;
                                (*it).position = old_position;
                                (*it).velocity = old_velocity;
                                physics_move(*it, time_m);

                                if((difference((*it).position, myfunctions[i2]) == old_state) ^ (dtime < 0))
                                {
                                    time_l = time_m;
                                }
                                else time_r = time_m;
                                time_m = (time_l + time_r) / 2;
                            }

                            (*it).position = old_position;
                            (*it).velocity = old_velocity;
                            physics_move(*it, time_m);

                            //cerr << "count= " << t_count << endl;
                        }

                        n = tangent(myfunctions[i2], (*it).position.x, (*it).position.z);
                        new_velocity = impact(n, (*it).velocity);
                        (*it).velocity = new_velocity;

                        if(precise_impact)
                        {
                            if(dtime > 0 && dtime > time_m) physics_move(*it, dtime - time_m);
                            else if(dtime < 0 && dtime < time_m) physics_move(*it, -fabs(dtime - time_m));
                        }

                        //break;
                    }
                }
                else if(old_state == DIFFERENCE_NAN && new_state != DIFFERENCE_NAN) (*it).states[i2] = new_state;
                else if(new_state == DIFFERENCE_NAN) (*it).states[i2] = DIFFERENCE_NAN;
            }
        }
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
    if(use_gravity) pt.acceleration = gravity;

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
