#ifndef IMPACT_H
#define IMPACT_H

#include <QtOpenGL>
#include "vect.h"
#include <vector>

using std::vector;

typedef enum { DRAW_LINES, DRAW_QUADS } draw_type_;
typedef enum { DRAW_POINTS, DRAW_OTHER } draw_point_type_;
typedef enum { COLOR_PREDEFINED, COLOR_VELOCITY } point_color_;
typedef long double number_t;

class Impact : public QGLWidget
{
private:
    //camera, view
    vect angle;
    vect position;
    draw_type_ draw_type;
    bool pause;
    unsigned int pause_manual;
    number_t speed_view;
    bool draw_velocity;
    bool draw_functions;
    bool draw_gravity_points;
    draw_point_type_ draw_point_type;
    number_t dt_step;
    point_color_ point_color;

    //physics
    bool precise_impact;
    bool use_gravity;
    number_t derivative_eps;
    number_t time;
    unsigned int impact_max_iterations;

    GLuint objects[2];
    GLuint texture[2];

    //world
    number_t step;
    number_t angle_step;
    number_t velocity;
    number_t dt;
    number_t graph_step;
    number_t M; //max_coord
    vect gravity;

    vector<point> mypoints;
    vector<point> mygravitypoints;
    vector<point> mypoints_defaults;
    vector<f_result (*)(number_t, number_t)> myfunctions;

public:
    Impact();
    void add_function(f_result(*f)(number_t, number_t));
    void add_point(vect position, vect velocity, vect color);
    void add_point(number_t x, number_t y, number_t z);
    void add_gravity_point(vect position, number_t mass);
    void add_point(number_t x, number_t y, number_t z, number_t vx, number_t vy, number_t vz);
    void add_points(f_result(*f)(number_t, number_t), number_t M, number_t step, vect velocity);
    void firework(vect position, number_t velocity, unsigned int N);
    void ftl();
    void set_gravity(number_t x, number_t y, number_t z);
    void set_dt(number_t x);
    void set_defaults();
protected:
    void keyPressEvent(QKeyEvent*);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void timerEvent(QTimerEvent *);

    void home();
    void graph(f_result(*f)(number_t, number_t), draw_type_ d_type);
    void graph_point(number_t, number_t, f_result(*f)(number_t, number_t));
    void draw_points_gl();
    void draw_functions_gl();
    int difference(vect coords, f_result(*f)(number_t, number_t));
    number_t derivative_x(f_result(*f)(number_t, number_t), number_t x, number_t y);
    number_t derivative_y(f_result(*f)(number_t, number_t), number_t x, number_t y);
    vect tangent(f_result(*f)(number_t, number_t), number_t x, number_t y);
    GLint ftl_mode(draw_type_ d_type);
    void physics_simple(point& pt, number_t dtime);
    void physics(number_t dtime);
    vect get_color(vect velocity);

    void points_defaults();
};

#endif // IMPACT_H
