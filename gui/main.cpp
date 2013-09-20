#include <QtGui/QApplication>
#include "draw.h"
#include <vect.h>
#include <math.h>

f_result plane_f(number_t x, number_t y)
{
    f_result res;

    res.coordinates.z = 0;
    res.color = vect(0.1, 0.1, 0.1);

    return(res);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Draw w;

    w.setClearColor(vect(0, 0, 0));

    double sq = 2;
    double st = 0.01;

    function plane;
    plane.first = (void*) plane_f;
    plane.second.xmin = -sq;
    plane.second.xmax = sq;
    plane.second.xstep = st;
    plane.second.ymin = -sq;
    plane.second.ymax = sq;
    plane.second.ystep = st;
    plane.second.type = function_info::T_COORDINATE;

    w.add_function(plane);

    w.add_point(vect(0, 0, 0), vect(0, 0, 0), vect(1, 1, 1), 0, vect(0, 0, 0), 0);
    for(int i = 0; i < 20; i++)
        w.add_point(vect(0, 0, 0), vect(0, 0, 0), vect(1, 0, 0), 0, vect(0, 0, 0), 0);


    w.ftl();
    w.show();
    return a.exec();
}


