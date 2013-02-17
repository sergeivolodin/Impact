#include <QtGui/QApplication>
#include "DEImg2.h"
#include <vect.h>
#include <math.h>
#include <iostream>

using std::cout;
using std::endl;

const number_t lineWidth = 1.5;
const number_t R = 5, r = 3;
const number_t YBottom = -3;
const number_t YTop = -YBottom;
const number_t a = 10, b = 7;
number_t b1;

f_result Circle(number_t t, number_t y, void* param)
{
    number_t R0 = (((number_t * ) param)[0]);
    f_result res;
    res.coordinates.x = R0 * cos(t);
    res.coordinates.y = R0 * sin(t);
    res.coordinates.z = (((number_t * ) param)[1]);

    res.color = vect(0, 0, 0);

    if(res.coordinates.z > 0)
    {
        if(R0 == R)
        {
            //big one
            if(t > M_PI)
                res.color = vect(0.9, 0.9, 0.9);
        }
        else
            //small one
            res.color = vect(0.9, 0.9, 0.9);
    }
    return(res);
}

void Lines()
{
    glLineWidth(lineWidth);
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

    glVertex3f(0, YBottom, 0);
    glVertex3f(0, b * 1.1, 0);
    glEnd();
}

void Points()
{
    glColor3f(0, 0, 0);
    glPointSize(10.0f);
    glBegin(GL_POINTS);

    //mass
    glVertex3f(-a, b, 0);
    glVertex3f(a, b, 0);

    glEnd();

    glPointSize(5.0f);

    glBegin(GL_POINTS);
    //mass center
    glVertex3f(0, b, 0);
    //C
    glVertex3f(0, b1, 0);
    //O
    glVertex3f(0, 0, 0);
    glEnd();
}

void Axis()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(-1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
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
    //Axis();
    Points();
    Lines();
}

int main(int argc, char *argv[])
{
    b1 = 2 * b / 3;

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
    circle1.second.lineWidth = lineWidth;
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
    other.second.lineWidth = lineWidth;
    other.second.drawNow = false;

    QApplication app(argc, argv);
    DEImg2 w;

    w.add_function(other);
    w.add_function(circle1);
    w.add_function(circle2);
    w.add_function(circle3);
    w.add_function(circle4);

    w.setCamera(vect(0, -9.95935, -44.9053), vect(0.188496, 0, 0));

    w.show();
    return app.exec();
}
