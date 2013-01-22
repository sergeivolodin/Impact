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
    function p, e, s, c1, c2, axis_, eVisible;

    p.first = (void*) plane;
    e.first = (void*) ellipsoid;
    s.first = (void*) sphere;
    c1.first = (void*) curve1;
    c2.first = (void*) curve2;
    axis_.first = (void*) axis;
    eVisible.first = (void*) ellipsoidVisible;

    p.second.type = function_info::T_COORDINATE;
    p.second.xmin = -20;
    p.second.xmax = 20;
    p.second.xstep = 0.5;
    p.second.ymin = -20;
    p.second.ymax = 20;
    p.second.ystep = 0.5;
    p.second.lineWidth = 1;
    p.second.useQuads = true;
    p.second.drawNow = false;
    p.second.sendCoord = false;

    e.second = p.second;
    e.second.type = function_info::T_PARAMETRIC;
    e.second.xmin = -M_PI / 2;
    e.second.xmax =  M_PI / 2;
    e.second.ymin = -M_PI;
    e.second.ymax =  M_PI;
    e.second.lineWidth = 1;
    e.second.drawNow = false;
    p.second.drawNow = false;

    p.second.useQuads = true;

    eVisible.second.type = function_info::T_PARAMETRIC;
    eVisible.second.xmin = 0;
    eVisible.second.xmax = 2 * M_PI;
    eVisible.second.xstep = 2 * M_PI / 1000;
    eVisible.second.ymin = 0;
    eVisible.second.ymax = 1;
    eVisible.second.ystep = 1;
    eVisible.second.lineWidth = 1;
    eVisible.second.useQuads = false;
    eVisible.second.sendCoord = true;
    eVisible.second.drawNow = true;

    s.second = e.second;
    s.second.lineWidth = 5;
    s.second.useQuads = true;
    s.second.drawNow = false;
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
    c1.second.drawNow = false;
    c2.second.drawNow = false;

    axis_.second.type = function_info::T_NONE;
    axis_.second.lineWidth = 1;
    axis_.second.drawNow = false;

    QApplication app(argc, argv);
    DzhanibekovEffect w;

    w.add_function(e);
    w.add_function(eVisible);
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
    c2.second.param = c1.second.param;
    ((curve_param *)(c1.second.param))->r = b;
    ((curve_param *)(c1.second.param))->color = vect(0, 0, 0);
    w.add_function(c1);
    w.add_function(c2);

    c1.second.lineWidth = 1;
    c2.second.lineWidth = 1;
    c1.second.param = new curve_param;
    ((curve_param *)(c1.second.param))->r = b + 0.05;
    ((curve_param *)(c1.second.param))->color = vect(0, 0, 0);
    c2.second.param = c1.second.param;
    w.add_function(c1);
    w.add_function(c2);

    c1.second.lineWidth = 1;
    c2.second.lineWidth = 1;
    c1.second.param = new curve_param;
    ((curve_param *)(c1.second.param))->r = b - 0.05;
    ((curve_param *)(c1.second.param))->color = vect(0, 0, 0);
    c2.second.param = c1.second.param;
    w.add_function(c1);
    w.add_function(c2);

    w.show();
    return app.exec();
}
