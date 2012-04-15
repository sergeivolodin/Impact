#include "impact.h"
#include "vect.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
#include <GL/glut.h>

Impact::Impact()
{
    startTimer(1);
    set_defaults();
    setWindowTitle("Impact");
}

void Impact::home()
{
    position = vect(0, 0, 0);
    angle = vect(0, 0, 0);
}

void Impact::set_defaults()
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

    impact_max_iterations = 15;
    gravity = vect(0, 0, 0);
    point_color = COLOR_PREDEFINED;


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

void Impact::keyPressEvent(QKeyEvent* a)
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
    else if(a->key() == Qt::Key_P) precise_impact ^= 1;
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
    else if(a->key() == Qt::Key_P)
    {
        /*cerr << "position: ";
        position;
        cerr << endl << "angle: ";
        << angle;
        cerr << endl << "velocity: " << velocity << endl;
        cerr << "functions q.: " << (myfunctions.size()) << endl;
        cerr << "points q.: " << (mypoints.size()) << endl;*/
    }
}

void Impact::points_defaults()
{
    unsigned int i;
    for(i = 0; i < mypoints.size(); i++)
        mypoints[i] = mypoints_defaults[i];
}


