#include <QtGui/QApplication>
#include "DEImg2.h"
#include <vect.h>
#include <math.h>
#include <iostream>

using std::cout;
using std::endl;

const number_t R = 5, r = 3;
const number_t YBottom = -3;
const number_t YTop = -YBottom;
const number_t a = 6, b = 2;
number_t b1;

f_result Circle(number_t t, number_t y, void* param)
{
    f_result res;
    res.coordinates.x = (((number_t * ) param)[0]) * cos(t);
    res.coordinates.y = (((number_t * ) param)[0]) * sin(t);
    res.coordinates.z = (((number_t * ) param)[1]);

    if(t >=0 && t <= M_PI && res.coordinates.z > 0)
        res.color = vect(0.9, 0.9, 0.9);
    else res.color = vect(0, 0, 0);
    return(res);
}

void Lines()
{
    glBegin(GL_LINES);
    glColor3f(0, 0, 0);
    glVertex3f(-R, YBottom, 0);
    glVertex3f(-R, YTop, 0);

    glVertex3f(R, YBottom, 0);
    glVertex3f(R, YTop, 0);

    glColor3f(0.9, 0.9, 0.9);
    glVertex3f(-r, YBottom, 0);
    glVertex3f(-r, YTop, 0);

    glVertex3f(r, YBottom, 0);
    glVertex3f(r, YTop, 0);
    glEnd();
}

void Points()
{
    glPointSize(10.0f);
    glBegin(GL_POINTS);
    glVertex3f(-a, b, 0);
    glVertex3f(a, b, 0);
    glVertex3f(0, b, 0);
    glVertex3f(0, b1, 0);
    glVertex3f(0, 0, 0);
    glEnd();
}

void Axis()
{
    glColor3f(0, 0, 0);
    //glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0);
    glVertex3f(-1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glEnd();

    //glColor3f(0, 1, 0);
//    glPointSize(10);
//    glBegin(GL_POINTS);
//    glVertex3f(-1, 0, 0);
//    glVertex3f(0, 1, 0);
//    glVertex3f(0, 0, 1);
//    glEnd();
}

void Other()
{
    Axis();
    Points();
    Lines();
}

int main(int argc, char *argv[])
{
    b1 = b / 2;

    function circle1, circle2, circle3, circle4, other;

    circle1.first = (void*) Circle;
    circle2.first = (void*) Circle;
    circle3.first = (void*) Circle;
    circle4.first = (void*) Circle;
    other.first = (void*) Other;

    circle1.second.type = function_info::T_PARAMETRIC;
    circle1.second.xmin = 0;
    circle1.second.xmax = 2 * M_PI;
    circle1.second.xstep = 2 * M_PI / 1000;
    circle1.second.ymin = 0;
    circle1.second.ymax = 0;
    circle1.second.ystep = 1;
    circle1.second.lineWidth = 1;
    circle1.second.useQuads = false;
    circle1.second.sendCoord = false;
    circle1.second.drawNow = false;
    circle1.second.param = new number_t[2];
    ((number_t*) circle1.second.param)[0] = R;
    ((number_t*) circle1.second.param)[1] = YBottom;

    circle2.second = circle1.second;
    circle2.second.param = new number_t[2];
    circle3.second = circle1.second;
    circle3.second.param = new number_t[2];
    circle4.second = circle1.second;
    circle4.second.param = new number_t[2];

    ((number_t*) circle2.second.param)[0] = r;
    ((number_t*) circle2.second.param)[1] = YBottom;

    ((number_t*) circle3.second.param)[0] = R;
    ((number_t*) circle3.second.param)[1] = YTop;

    ((number_t*) circle4.second.param)[0] = r;
    ((number_t*) circle4.second.param)[1] = YTop;

    other.second.type = function_info::T_NONE;
    other.second.lineWidth = 1;
    other.second.drawNow = false;

    QApplication app(argc, argv);
    DEImg2 w;

    w.add_function(other);
    w.add_function(circle1);
    w.add_function(circle2);
    w.add_function(circle3);
    w.add_function(circle4);

    w.show();
    return app.exec();
}