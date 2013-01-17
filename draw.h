#ifndef DRAW_H
#define DRAW_H

#include <QtOpenGL>
#include "vect.h"
#include "impact.h"
#include <vector>

using std::vector;

typedef enum { DRAW_LINES, DRAW_QUADS } draw_type_;
typedef enum { DRAW_POINTS, DRAW_OTHER } draw_point_type_;
typedef long double number_t;

class DzhanibekovEffect;

class Draw : public Impact, public QGLWidget
{
friend class DzhanibekovEffect;

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
    draw_point_type_ draw_point_type;
    number_t dt_step;
    unsigned int dt_for_views;

    number_t step;
    number_t angle_step;
    number_t velocity;
    number_t graph_step;

    vector<GLuint> objects[2];

    vect clearColor;

    void keyPressEvent(QKeyEvent*);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void timerEvent(QTimerEvent *);

    void home();
    void graph_point(number_t, number_t, function);
    void draw_points_gl();
    void draw_functions_gl();

    void ftl_clear();
    void ftl_one(function f, draw_type_ d_type);

public:
    Draw();

    void ftl_saved(draw_type_ d_type);

    void ftl_f(function f);
    void ftl();
    void set_defaults();
    void set_dt_for_views(unsigned int x);
    void set_paused(bool x);
    void graph(function, draw_type_ d_type);

    void setClearColor(vect);
};
#endif // DRAW_H
