#include "impact.h"
#include "vect.h"
#include <math.h>
#include <iostream>
#include <stack>
#include <stdlib.h>
#include <GL/glut.h>

using std::stack;

GLint Impact::ftl_mode(draw_type_ d_type)
{
    GLint lid = glGenLists(1);

    glNewList(lid, GL_COMPILE);

    vector<f_result (*)(number_t, number_t)>::iterator it;
    for(it = myfunctions.begin(); it != myfunctions.end(); it++) graph((*it), d_type);

    glEndList();

    return(lid);
}
void Impact::ftl()
{
    objects[0]=ftl_mode(DRAW_LINES);
    objects[1]=ftl_mode(DRAW_QUADS);
}

void Impact::initializeGL()
{
    Impact::maximumSize();
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    ftl();
}

void Impact::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (number_t)w / (number_t)h, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Impact::graph_point(number_t x, number_t z, f_result(*f)(number_t, number_t))
{
    f_result t_res = f(x, z);
    glColor3f(t_res.color.x, t_res.color.y, t_res.color.z);
    glVertex3f(x, t_res.z, z);
}

void Impact::draw_points_gl()
{
    vector<point>::iterator it;
    static vect t_vect;

    if(draw_point_type == DRAW_POINTS)
    {
        //glPointSize(10.0f);
        glBegin(GL_POINTS);

        for(it = mypoints.begin(); it != mypoints.end(); it++)
        {
            if(point_color == COLOR_PREDEFINED)
                glColor3f((*it).color.x, (*it).color.y, (*it).color.z);
            else if(point_color == COLOR_VELOCITY)
            {
                t_vect = get_color((*it).velocity);
                glColor3f(t_vect.x, t_vect.y, t_vect.z);
            }
            glVertex3f((*it).position.x, (*it).position.y, (*it).position.z);
        }

        glEnd();
    }
    else if(draw_point_type == DRAW_OTHER)
    {
        glBegin(GL_LINES);
        stack<point> triangles;

        point t_point;

        const number_t magic_maxlen = pow(10, 2);
        for(unsigned int i = 0; i < mypoints.size(); i++)
        {
            if(triangles.empty()) triangles.push(mypoints[i]);
            else if(triangles.size() == 2)
            {
                while(!triangles.empty())
                {
                    t_point = triangles.top();
                    triangles.pop();
                    if(point_color == COLOR_PREDEFINED)
                        glColor3f(t_point.color.x, t_point.color.y, t_point.color.z);
                    else if(point_color == COLOR_VELOCITY)
                    {
                        t_vect = get_color(t_point.velocity);
                        glColor3f(t_vect.x, t_vect.y, t_vect.z);
                    }
                    glVertex3f(t_point.position.x, t_point.position.y, t_point.position.z);
                }
            }
            else
            {
                t_vect = triangles.top().position;
                t_vect -= mypoints[i].position;
                if(t_vect.abs_2() <= magic_maxlen) triangles.push(mypoints[i]);
            }
        }

        glEnd();
    }

    if(draw_velocity)
    {
        glBegin(GL_LINES);

        for(it = mypoints.begin(); it != mypoints.end(); it++)
        {
            if(point_color == COLOR_PREDEFINED)
                glColor3f((*it).color.x, (*it).color.y, (*it).color.z);
            else if(point_color == COLOR_VELOCITY)
            {
                t_vect = get_color((*it).velocity);
                glColor3f(t_vect.x, t_vect.y, t_vect.z);
            }
            glVertex3f((*it).position.x, (*it).position.y, (*it).position.z);
            glVertex3f((*it).position.x + (*it).velocity.x * dt * speed_view,
                       (*it).position.y + (*it).velocity.y * dt * speed_view,
                       (*it).position.z + (*it).velocity.z * dt * speed_view);
        }

        glEnd();
    }

    if(draw_gravity_points)
    {
        glPointSize(10.0f);
        glBegin(GL_POINTS);
        glColor3f(1, 1, 1);
        for(it = mygravitypoints.begin(); it != mygravitypoints.end(); it++)
        {
            glVertex3f((*it).position.x, (*it).position.y, (*it).position.z);
        }
        glEnd();
        glPointSize(1.0f);
    }
}

void Impact::draw_functions_gl()
{
    if(draw_functions)
    {
        if(draw_type == DRAW_LINES) glCallList(objects[0]);
        if(draw_type == DRAW_QUADS) glCallList(objects[1]);
    }
}

void Impact::graph(f_result(*f)(number_t, number_t), draw_type_ d_type)
{
    number_t x, z;

    if(d_type == DRAW_LINES)
    {
        glBegin(GL_LINES);
        for(x = -M; x <= M; x += graph_step)
            for(z = -M; z <= M; z += graph_step)
            {
                graph_point(x, z, f);
                graph_point(x + graph_step, z, f);
                graph_point(x, z, f);
                graph_point(x, z + graph_step, f);
            }
    }
    else if(d_type == DRAW_QUADS)
    {
        glBegin(GL_QUADS);
        for(x = -M; x <= M; x += graph_step)
            for(z = -M; z <= M; z += graph_step)
            {
                graph_point(x, z, f);
                graph_point(x + graph_step, z, f);
                graph_point(x + graph_step, z + graph_step, f);
                graph_point(x, z + graph_step, f);
            }
    }

    glEnd();
}

void Impact::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glTranslatef(0, 0, 0);

    draw_functions_gl();
    draw_points_gl();

    glLoadIdentity();
    glRotatef(degrees(angle.z), 0, 0, 1);
    glRotatef(degrees(angle.x), 1, 0, 0);
    glRotatef(degrees(angle.y), 0, 1, 0);
    glTranslatef(position.x, position.y, position.z);
}
