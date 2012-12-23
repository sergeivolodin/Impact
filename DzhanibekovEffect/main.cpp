#include <QtGui/QApplication>
#include "DzhanibekovEffect.h"
#include "Surfaces.h"
#include <vect.h>
#include <math.h>
#include <iostream>

using std::cout;
using std::endl;

void axis()
{
    glColor3f(0, 0, 0);
    //glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(1.5 * a, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1.5 * c, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1.5 * b);
    glEnd();

    //glColor3f(0, 1, 0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex3f(a, 0, 0);
    glVertex3f(0, c, 0);
    glVertex3f(0, 0, b);
    glEnd();
}

int main(int argc, char *argv[])
{
    function p, e, s, c1, c2, axis_;

    p.first = (void*) plane;
    e.first = (void*) ellipsoid;
    s.first = (void*) sphere;
    c1.first = (void*) curve1;
    c2.first = (void*) curve2;
    axis_.first = (void*) axis;

    p.second.type = function_info::T_COORDINATE;
    p.second.xmin = -20;
    p.second.xmax = 20;
    p.second.xstep = 0.5;
    p.second.ymin = -20;
    p.second.ymax = 20;
    p.second.ystep = 0.5;
    p.second.lineWidth = 1;
    p.second.useQuads = true;

    e.second = p.second;
    e.second.type = function_info::T_PARAMETRIC;
    e.second.xmin = -M_PI / 2;
    e.second.xmax =  M_PI / 2;
    e.second.ymin = -M_PI;
    e.second.ymax =  M_PI;
    e.second.lineWidth = 1;
    p.second.useQuads = true;

    s.second = e.second;
    s.second.lineWidth = 1;
    s.second.useQuads = true;
    c1.second = e.second;
    c1.second.xmin = 0;
    c1.second.xmax = 0;
    c1.second.xstep = 1;
    c1.second.ymin = 0;
    c1.second.ymax = 10 * M_PI;
    c1.second.ystep = 2 * M_PI / 10000;
    c1.second.useQuads = false;
    c2.second = c1.second;
    c1.second.lineWidth = 1;
    c2.second.lineWidth = 1;

    axis_.second.type = function_info::T_NONE;
    axis_.second.lineWidth = 1;

    QApplication app(argc, argv);
    DzhanibekovEffect w;

    w.add_function(e);
    w.add_function(axis_);

    for(number_t r = c; r <= a; r += 0.5)
    {
        c1.second.param = new curve_param;
        ((curve_param *)(c1.second.param))->r = r;
        ((curve_param *)(c1.second.param))->color = vect(0.1, 0.1, 0.1);
        c2.second.param = c1.second.param;
        w.add_function(c1);
        w.add_function(c2);
    }

    c1.second.lineWidth = 5;
    c2.second.lineWidth = 5;
    c1.second.param = new curve_param;
    ((curve_param *)(c1.second.param))->r = b;
    //((curve_param *)(c1.second.param))->color = vect(1, 0, 0);
    c2.second.param = c1.second.param;
    w.add_function(c1);
    w.add_function(c2);

    c1.second.lineWidth = 1;
    c2.second.lineWidth = 1;
    c1.second.param = new curve_param;
    ((curve_param *)(c1.second.param))->r = b + 0.05;
    //((curve_param *)(c1.second.param))->color = vect(1, 0, 0);
    c2.second.param = c1.second.param;
    w.add_function(c1);
    w.add_function(c2);

    c1.second.lineWidth = 1;
    c2.second.lineWidth = 1;
    c1.second.param = new curve_param;
    ((curve_param *)(c1.second.param))->r = b - 0.05;
    //((curve_param *)(c1.second.param))->color = vect(1, 0, 0);
    c2.second.param = c1.second.param;
    w.add_function(c1);
    w.add_function(c2);

    w.show();
    return app.exec();
}
