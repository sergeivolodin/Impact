#include "impact.h"
#include "vect.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

void Impact::physics(number_t dtime)
{
    vector<point>::iterator it;
    unsigned int i2;
    static vect old_position, old_velocity, n, new_velocity;
    static number_vect_t time_l, time_m, time_r;
    static unsigned int t_count;

    for(it = mypoints.begin(); it != mypoints.end(); it++)
    {
        if(precise_impact)
        {
            old_position = (*it).position;
            old_velocity = (*it).velocity;
        }
        physics_simple((*it), dtime);


        if(fabs((*it).position.x) <= M && fabs((*it).position.z) < M)
        {
            for(i2 = 0; i2 < myfunctions.size(); i2++)
            {
                int old_state = (*it).states[i2],
                    new_state = difference((*it).position, myfunctions[i2]);

                if(new_state != old_state)
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
                            physics_simple(*it, time_m);

                            if((difference((*it).position, myfunctions[i2]) == old_state) ^ (dtime < 0))
                            {
                                time_l = time_m;
                            }
                            else time_r = time_m;
                            time_m = (time_l + time_r) / 2;
                        }

                        (*it).position = old_position;
                        (*it).velocity = old_velocity;
                        physics_simple(*it, time_m);

                        //cerr << "count= " << t_count << endl;
                    }

                    n = tangent(myfunctions[i2], (*it).position.x, (*it).position.z);
                    new_velocity = impact(n, (*it).velocity);
                    (*it).velocity = new_velocity;

                    if(precise_impact)
                    {
                        if(dtime > 0 && dtime > time_m) physics_simple(*it, dtime - time_m);
                        else if(dtime < 0 && dtime < time_m) physics_simple(*it, -fabs(dtime - time_m));
                    }

                    break;
                }
            }
        }
    }
    time += dtime;
}

void Impact::physics_simple(point& pt, number_t dtime)
{
    vect acc(0, 0, 0);
    static vect t_position;
    if(use_gravity) acc = gravity;

    vector<point>::iterator it;
    for(it = mygravitypoints.begin(); it != mygravitypoints.end(); it++)
    {
        t_position = (*it).position;
        t_position -= pt.position;
        if(t_position.abs_2() != 0)
        {
            acc += (t_position * ((*it).mass / pow(fabs(t_position.abs()), 3)));
        }
    }

    //acc *= dtime / fabs(dtime);

    pt.position += (pt.velocity * dtime) + (acc * (dtime * dtime / 2.));
    pt.velocity += acc * dtime;
}


