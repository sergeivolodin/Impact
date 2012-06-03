#include "impact.h"
#include "vect.h"
#include <math.h>
#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <GL/glut.h>

using std::cout;
using std::endl;

using std::string;
using std::stringstream;

using std::vector;
using std::map;

string Impact::print_points()
{
    stringstream ss;

    vector<point>::iterator it;
    unsigned int i;
    ss << "#### POINTS DUMP BEGIN ###" << endl;
    for(it = mypoints.begin(), i = 0; it != mypoints.end(); it++, i++)
    {
        ss << "pt #" << i << endl;
        ss << print_point(*it, true);
        ss << endl;
    }
    ss << "#### POINTS DUMP END ###" << endl << endl;

    string res = ss.str();
    return(res);
}

string Impact::print_status()
{
    stringstream ss;
    vect momentum(0, 0, 0), angular_momentum(0, 0, 0);
    number_t mass = 0, kinetic_energy = 0, relative_kinetic_energy = 0;
    vector<point>::iterator it;
    ss << "time = " << time << endl;

    for(it = mypoints.begin(); it != mypoints.end(); it++)
    {
        momentum += (*it).velocity * (*it).mass;
        angular_momentum += (*it).angular_velocity * (*it).moment_of_inertia;
        mass += (*it).mass;
        kinetic_energy += (*it).mass  * (*it).velocity.abs_2() / 2;
        relative_kinetic_energy += (*it).mass * (1 / sqrt(1 - pow((*it).velocity.abs() / c, 2)) - 1);
    }

    ss << "momentum = " << momentum.print() << endl;
    ss << "angular_momentum = " << angular_momentum.print() << endl;
    ss << "rest_energy = " << mass * pow(c, 2) << endl;
    ss << "kinetic_energy = " << kinetic_energy << endl;
    ss << "relative_kinetic_energy = " << relative_kinetic_energy * pow(c, 2) << endl;
    return(ss.str());
}

string Impact::print_point(point &pt, bool print_acceleration)
{
    stringstream ss;
    ss << "position: " << pt.position.print() << endl;
    ss << "velocity [" << pt.velocity.abs() << "]: " << pt.velocity.print() << endl;
    if(print_acceleration) ss << "acceleration [" << pt.acceleration.abs() << "]: " << pt.acceleration.print() << endl;

    string res = ss.str();
    return(res);
}

void Impact::points_defaults()
{
    paths.clear();

    unsigned int i;
    for(i = 0; i < mypoints.size(); i++)
        mypoints[i] = mypoints_defaults[i];
}

