#include "draw.h"
#include "vect.h"
#include <math.h>
#include <iostream>
#include <stack>
#include <stdlib.h>
#include <GL/glut.h>

using std::stack;

GLint Draw::ftl_mode(draw_type_ d_type)
{
    GLint lid = glGenLists(1);

    glNewList(lid, GL_COMPILE);

    vector<f_result (*)(number_t, number_t)>::iterator it;
    for(it = myfunctions.begin(); it != myfunctions.end(); it++) graph((*it), d_type);

    glEndList();

    return(lid);
}
void Draw::ftl()
{
    objects[0]=ftl_mode(DRAW_LINES);
    objects[1]=ftl_mode(DRAW_QUADS);
}

void Draw::initializeGL()
{
    Draw::maximumSize();
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    ftl();
}

void Draw::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (number_t)w / (number_t)h, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Draw::graph_point(number_t x, number_t z, f_result(*f)(number_t, number_t))
{
    f_result t_res = f(x, z);
    glColor3f(t_res.color.x, t_res.color.y, t_res.color.z);
    glVertex3f(x, t_res.z, z);
}

void Draw::draw_points_gl()
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

void Draw::draw_functions_gl()
{
    if(draw_functions)
    {
        if(draw_type == DRAW_LINES) glCallList(objects[0]);
        if(draw_type == DRAW_QUADS) glCallList(objects[1]);
    }
}

void Draw::graph(f_result(*f)(number_t, number_t), draw_type_ d_type)
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

void Draw::paintGL()
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

void Draw::set_dt_for_views(unsigned int x)
{
    dt_for_views = x;
}

void Draw::timerEvent(QTimerEvent *)
{
    //if(time >= 200 && dt > 0) dt = -dt;

    forward(velocity, &position, &angle);

    static unsigned int views_count = 1;
    if(views_count == dt_for_views)
    {
        update();
        views_count = 1;
    }
    else views_count++;

    //if(time < 0 ) return;
    if(!pause || pause_manual)
    {
        if(pause_manual) pause_manual--;
        physics(dt);
    }
}

Draw::Draw()
{
    startTimer(0.1);
    set_defaults();
    setWindowTitle("Impact");
}

void Draw::home()
{
    position = vect(0, 0, 0);
    angle = vect(0, 0, 0);
}

void Draw::set_defaults()
{
    home();
    speed_view = 5;
    step = 0.5;
    angle_step = M_PI / 50;
    dt_step = 0.01;
    dt = dt_step;
    graph_step = 0.2;
    M = 30;
    draw_type = DRAW_LINES;
    derivative_eps = 1e-2;

    impact_max_iterations = 10;
    dt_for_views = 4;
    gravity = vect(0, 0, 0);
    point_color = COLOR_PREDEFINED;
    use_gravity_points = true;
    use_gravity_n2 = true;


    velocity = 0;
    pause = true;
    pause_manual = 0;
    draw_velocity = false;
    draw_functions = true;
    draw_gravity_points = true;
    draw_point_type = DRAW_POINTS;
    precise_impact = true;
    use_gravity = true;
    ftl();
}

void Draw::set_paused(bool x)
{
    pause = x;
}

void Draw::keyPressEvent(QKeyEvent* a)
{
    if(a->key() == Qt::Key_Up) forward(step, &position, &angle);
    else if(a->key() == Qt::Key_Down) forward(-step, &position, &angle);
    else if(a->key() == Qt::Key_A)
    {
        angle.y -= angle_step;
        while(angle.y <= -2 * M_PI) angle.y += 2 * M_PI;
    }
    else if(a->key() == Qt::Key_D)
    {
        angle.y += angle_step;
        while(angle.y >= 2 * M_PI) angle.y -= 2 * M_PI;
    }
    else if(a->key() == Qt::Key_W)
    {
        if(angle.x >= -M_PI/2) angle.x -= angle_step;
    }
    else if(a->key() == Qt::Key_S)
    {
        if(angle.x <= M_PI/2) angle.x += angle_step;
    }
    else if(a->key() == Qt::Key_Home) home();
    else if(a->key() == Qt::Key_PageUp) velocity += step;
    else if(a->key() == Qt::Key_PageDown) velocity -= step;
    else if(a->key() == Qt::Key_End) velocity = 0;
    else if(a->key() == Qt::Key_Shift) angle.x = 0;
    else if(a->key() == Qt::Key_T)
    {
        if(draw_type == DRAW_LINES) draw_type = DRAW_QUADS;
        else draw_type = DRAW_LINES;
    }
    else if(a->key() == Qt::Key_Y)
    {
        if(draw_point_type == DRAW_OTHER) draw_point_type = DRAW_POINTS;
        else draw_point_type = DRAW_OTHER;
    }
    //else if(a->key() == Qt::Key_P) precise_impact ^= 1;
    else if(a->key() == Qt::Key_G) use_gravity ^= 1;
    else if(a->key() == Qt::Key_B)
    {
        if(point_color == COLOR_PREDEFINED) point_color = COLOR_VELOCITY;
        else point_color = COLOR_PREDEFINED;
    }
    else if(a->key() == Qt::Key_Space)
    {
        points_defaults();
        pause = true;
    }
    else if(a->key() == Qt::Key_Pause || a->key() == Qt::Key_F1)
    {
        pause = !pause;
        pause_manual = 0;
    }
    else if(a->key() == Qt::Key_Tab) pause_manual++;
    else if(a->key() == Qt::Key_F) draw_functions ^= 1;
    else if(a->key() == Qt::Key_V) draw_velocity ^= 1;
    else if(a->key() == Qt::Key_Z) dt -= dt_step;
    else if(a->key() == Qt::Key_X) dt = 0;
    else if(a->key() == Qt::Key_C) dt += dt_step;
    else if(a->key() == Qt::Key_P) print_points();
}
