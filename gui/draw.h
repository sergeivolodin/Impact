#ifndef DRAW_H
#define DRAW_H

#include <QtOpenGL>
#include "vect.h"
#include "impact.h"
#include <vector>

using std::vector;

typedef enum { DRAW_LINES, DRAW_QUADS } draw_type_;
typedef enum { DRAW_POINTS, DRAW_OTHER } draw_point_type_;
typedef enum { COLOR_PREDEFINED, COLOR_VELOCITY } point_color_;
typedef long double number_t;

class Draw : public Impact, public QGLWidget
{
private:
    //camera, view
    vect angle;
    vect position;
    draw_type_ draw_type;
    bool pause;
    unsigned int pause_manual;
    number_t speed_view;
    bool draw_angular_velocity;
    bool draw_velocity;
    bool draw_path;
    bool draw_functions;
    bool draw_gravity_points;
    draw_point_type_ draw_point_type;
    number_t dt_step;
    point_color_ point_color;
    unsigned int dt_for_views;

    number_t step;
    number_t angle_step;
    number_t velocity;
    number_t graph_step;

    GLuint objects[2];
    GLuint texture[2];

public:
    Draw();

    void ftl();
    void set_defaults();
    void set_dt_for_views(unsigned int x);
    void set_paused(bool x);
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

    GLint ftl_mode(draw_type_ d_type);
};

#endif // DRAW_H
