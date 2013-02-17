#include "draw.h"
#include "vect.h"
#include <math.h>
#include <iostream>
#include <sstream>
#include <stack>
#include <stdlib.h>
#include <GL/glut.h>

using std::cout;
using std::cerr;
using std::endl;

using std::stringstream;

using std::stack;

void Draw::ftl_one(function f, draw_type_ d_type)
{
    GLint lid = glGenLists(1);

    glNewList(lid, GL_COMPILE);
    graph(f, d_type);
    glEndList();

    cout << "created" << lid << endl;

    if(d_type == DRAW_LINES)
        objects[0].push_back(lid);
    if(d_type == DRAW_QUADS)
        objects[1].push_back(lid);
}

void Draw::ftl()
{
    ftl_saved(DRAW_LINES);
    ftl_saved(DRAW_QUADS);
}

void Draw::ftl_saved(draw_type_ d_type)
{
    vector<function>::iterator it;
    for(it = myfunctions.begin(); it != myfunctions.end(); it++)
        ftl_one(*it, d_type);
}

void Draw::ftl_f(function f)
{
    ftl_one(f, DRAW_LINES);
    ftl_one(f, DRAW_QUADS);
}

void Draw::ftl_clear()
{
    vector<GLuint>::iterator it;
    for(it = objects[0].begin(); it != objects[0].end(); it++)
    {
        glDeleteLists((*it), 1);
        glDeleteLists((*it), 1);
    }

    for(it = objects[1].begin(); it != objects[1].end(); it++)
    {
        glDeleteLists((*it), 1);
        glDeleteLists((*it), 1);
    }
}

void Draw::initializeGL()
{
    Draw::maximumSize();
    glShadeModel(GL_SMOOTH);
    glClearColor(clearColor.x, clearColor.y, clearColor.z, 0.0f);
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
    gluPerspective(45.0f, (number_t)w / (number_t)h, 0.1f, 10000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Draw::graph_point(number_t x, number_t z, function f)
{
    if(f.second.sendCoord)
        f.second.param = &visiblePosition;
        //f.second.param = &position;

    f_result t_res = ((f_result (*)(number_t, number_t, void*))(f.first))(x, z, f.second.param);

    glColor3f(t_res.color.x, t_res.color.y, t_res.color.z);
    if(f.second.type == function_info::T_COORDINATE)
        glVertex3f(x, t_res.coordinates.z, z);
    else if(f.second.type == function_info::T_PARAMETRIC)
        /*
         * ( 1 0 0 )
         * ( 0 0-1 )
         * ( 0 1 0 )
         */
        glVertex3f(t_res.coordinates.x, -t_res.coordinates.z, t_res.coordinates.y);
        //glVertex3f(t_res.coordinates.x, t_res.coordinates.y, t_res.coordinates.z);
}

void Draw::draw_points_gl()
{
    vector<point>::iterator it, it1;
    static vect t_vect;
    static point t_point;

    if(draw_path)
    {
        glBegin(GL_LINES);
        vector<point> path;
        for(it = mypoints.begin(); it != mypoints.end(); it++)
        {
            path = paths[ &(*it) ];
            it1 = path.begin();
            if(it1 != path.end())
            {
                t_point = *it1;
                it1++;

                for(; it1 != path.end(); it1++)
                {
                    glColor3f(t_point.color.x, t_point.color.y, t_point.color.z);
                    glVertex3f(t_point.position.x, t_point.position.y, t_point.position.z);

                    glColor3f((*it1).color.x, (*it1).color.y, (*it1).color.z);
                    glVertex3f((*it1).position.x, (*it1).position.y, (*it1).position.z);
                    t_point = *it1;
                }
            }
        }
        glEnd();
    }

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

    if(draw_angular_velocity)
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
            glVertex3f((*it).position.x + (*it).angular_velocity.x * dt * speed_view,
                       (*it).position.y + (*it).angular_velocity.y * dt * speed_view,
                       (*it).position.z + (*it).angular_velocity.z * dt * speed_view);
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
}

void Draw::draw_functions_gl()
{
    if(draw_functions)
    {
        static vector<GLuint>::iterator it;
        static int j;
        if(draw_type == DRAW_LINES) j = 0;
        if(draw_type == DRAW_QUADS) j = 1;

        for(it = objects[j].begin(); it != objects[j].end(); it++)
        {
            glCallList(*it);
        }

        static vector<function>::iterator it1;

        visiblePosition.x =  position.x;
        visiblePosition.y =  position.z;
        visiblePosition.z = -position.y;

        for(it1 = myfunctions.begin(); it1 != myfunctions.end(); it1++)
            if((*it1).second.drawNow) graph((*it1), draw_type);
    }
}

void Draw::graph(function f, draw_type_ d_type)
{
    glLineWidth(f.second.lineWidth);
    if(f.second.type == function_info::T_NONE)
    {
        ((void (*)())(f.first))();
        return;
    }

    number_t x, z;

    if(d_type == DRAW_LINES || !f.second.useQuads)
    {
        glBegin(GL_LINES);
        for(x = f.second.xmin; x <= f.second.xmax; x += f.second.xstep)
            for(z = f.second.ymin; z <= f.second.ymax; z += f.second.ystep)
            {
                graph_point(x, z, f);
                graph_point(x + f.second.xstep, z, f);
                graph_point(x, z, f);
                graph_point(x, z + f.second.ystep, f);
            }
    }
    else if(d_type == DRAW_QUADS)
    {
        glBegin(GL_QUADS);
        for(x = f.second.xmin; x <= f.second.xmax; x += f.second.xstep)
            for(z = f.second.ymin; z <= f.second.ymax; z += f.second.ystep)
            {
                graph_point(x, z, f);
                graph_point(x + f.second.xstep, z, f);
                graph_point(x + f.second.xstep, z + f.second.ystep, f);
                graph_point(x, z + f.second.ystep, f);
            }
    }

    glLineWidth(1);
    glEnd();
}

void Draw::setCamera(vect n_position, vect n_angle)
{
    angle = n_angle;
    position = n_position;
}

string Draw::print_coordinates()
{
    stringstream ss;
    ss << "p\t" << position.print() << "\t";
    ss << "a\t" << angle.print() << endl;
    return(ss.str());
}

void Draw::setClearColor(vect nC)
{
    clearColor = nC;
    initializeGL();
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
    forward(velocity, &position, &angle);

    static unsigned int views_count = 1;
    if(views_count == dt_for_views)
    {
        update();
        views_count = 1;
    }
    else views_count++;

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
    clearColor.x = clearColor.y = clearColor.z = 1;
}

void Draw::home()
{
    position = vect(0, 0, 0);
    angle = vect(0, 0, 0);
}

void Draw::set_defaults()
{
    home();
    speed_view = 15;
    step = 0.5;
    angle_step = M_PI / 50;
    dt_step = 0.01;
    dt = dt_step;
    graph_step = 0.2;
    M = 50;
    draw_type = DRAW_LINES;
    derivative_eps = 1e-2;

    impact_max_iterations = 10;
    dt_for_views = 4;
    gravity = vect(0, 0, 0);
    point_color = COLOR_PREDEFINED;
    use_gravity_n2 = true;

    velocity = 0;
    pause = true;
    pause_manual = 0;
    draw_velocity = false;
    draw_angular_velocity = false;
    draw_functions = true;
    draw_point_type = DRAW_POINTS;
    precise_impact = true;
    use_gravity = true;

    draw_path = false;
    track_path = false;

    G = 6.67384E-11;
    c = 299792458;
    use_gravitomagnetism_force = false;
    use_gravitomagnetism_torque = false;
}

void Draw::set_paused(bool x)
{
    pause = x;
}

void Draw::keyPressEvent(QKeyEvent* a)
{
    //movement
    if(a->key() == Qt::Key_Up) forward(step, &position, &angle);
    else if(a->key() == Qt::Key_Down) forward(-step, &position, &angle);
    else if(a->key() == Qt::Key_Home) home();

    //rotation
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
    else if(a->key() == Qt::Key_Shift) angle.x = 0;

    //velocity
    else if(a->key() == Qt::Key_PageUp) velocity += step;
    else if(a->key() == Qt::Key_PageDown) velocity -= step;
    else if(a->key() == Qt::Key_End) velocity = 0;

    //draw
    else if(a->key() == Qt::Key_T)
    {
        if(draw_type == DRAW_LINES) draw_type = DRAW_QUADS;
        else draw_type = DRAW_LINES;
    }
    else if(a->key() == Qt::Key_B)
    {
        if(point_color == COLOR_PREDEFINED) point_color = COLOR_VELOCITY;
        else point_color = COLOR_PREDEFINED;
    }
    else if(a->key() == Qt::Key_F) draw_functions ^= 1;
    else if(a->key() == Qt::Key_V) draw_velocity ^= 1;
    else if(a->key() == Qt::Key_L) draw_angular_velocity ^= 1;
    else if(a->key() == Qt::Key_0) draw_path ^= 1;

    //states
    else if(a->key() == Qt::Key_Space)
    {
        points_defaults();
        pause = true;
    }
    else if(a->key() == Qt::Key_Pause || a->key() == Qt::Key_F1)
    {
        pause ^= 1;
        pause_manual = 0;
    }
    else if(a->key() == Qt::Key_Tab) pause_manual++;
    else if(a->key() == Qt::Key_Z) dt -= dt_step;
    else if(a->key() == Qt::Key_X) dt = 0;
    else if(a->key() == Qt::Key_C) dt += dt_step;

    //other
    else if(a->key() == Qt::Key_G) use_gravity ^= 1;
    else if(a->key() == Qt::Key_P) cout << print_points();
    else if(a->key() == Qt::Key_Q) cout << print_status();
    else if(a->key() == Qt::Key_9) track_path ^= 1;
    else if(a->key() == Qt::Key_N) cerr << print_coordinates();
}
