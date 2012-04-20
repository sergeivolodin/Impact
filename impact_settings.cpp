#include "impact.h"
#include "vect.h"
#include <math.h>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <GL/glut.h>

using std::cerr;
using std::endl;

using std::vector;

void Impact::print_points()
{
    vector<point>::iterator it;
    unsigned int i;
    cerr << "#### POINTS DUMP BEGIN ###" << endl;
    for(it = mypoints.begin(), i = 0; it != mypoints.end(); it++, i++)
    {
        cerr << "pt #" << i << endl;
        print_point(*it);
        cerr << endl;
    }
    cerr << "#### POINTS DUMP END ###" << endl << endl;
}
void Impact::print_point(point &pt)
{
    cerr << "position: " << pt.position.print() << endl;
    cerr << "velocity [" << pt.velocity.abs() << "]: " << pt.velocity.print() << endl;
    cerr << "acceleration [" << pt.acceleration.abs() << "]: " << pt.acceleration.print() << endl;
}

void Impact::points_defaults()
{
    unsigned int i;
    for(i = 0; i < mypoints.size(); i++)
        mypoints[i] = mypoints_defaults[i];
}
