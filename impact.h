#ifndef IMPACT_H
#define IMPACT_H

#include "vect.h"
#include <string>
#include <map>
#include <vector>

using std::vector;
using std::map;
using std::pair;
using std::string;

typedef long double number_t;
typedef enum { COLOR_PREDEFINED, COLOR_VELOCITY } point_color_;

class Impact
{
friend class Draw;
private:
    //physics switches
    bool use_gravity;
    bool use_gravity_n2;
    bool use_gravitomagnetism_force;
    bool use_gravitomagnetism_torque;
    number_t derivative_eps;
    number_t time;

    //physics constants
    number_t G;
    number_t c;
    vect gravity;

    //simulation
    number_t dt;
    number_t M; //max_coord

    //switches
    bool track_path;
    bool precise_impact;
    point_color_ point_color;
    unsigned int impact_max_iterations;

    //storage
    vector<point> mypoints;
    vector<point> mypoints_defaults;
    vector<function> myfunctions;
    map< point*, vector<point> > paths;

    static const int DIFFERENCE_NAN = 2;

    void points_defaults();

    int difference(vect coords, function);
    vect tangent(function, number_t x, number_t y);

    void physics_set_acceleration(point& pt);
    void physics_move(point& pt, number_t dtime);
    void physics_impact(unsigned int f, point& p_old, point& p_new, number_t dtime);
    vect physics_gravity(point& p1, point& p2);
    pair<vect, vect> physics_gravitomagnetism(point& p1, point& p2);

    vect get_point_color(point& t_point);
    void save_points();

public:
    Impact();

    void add_function(function);
    void add_point(vect position, vect velocity, vect color, number_t mass, vect angular_velocity, number_t moment_of_inertia);
    void add_points(function, number_t M, number_t step, vect velocity, number_t mass, vect angular_velocity, number_t moment_of_inertia);
    void firework(vect position, number_t velocity, number_t mass, vect angular_velocity, number_t moment_of_inertia, unsigned int N);

    void set_gravity(vect x);
    void set_track_path(bool x);
    void set_dt(number_t x);
    void set_use_gravity_n2(bool x);
    void set_use_gravitomagnetism_force(bool x);
    void set_use_gravitomagnetism_torque(bool x);
    string print_points();
    string print_point(point& pt, bool print_acceleration);
    string print_status();

    number_t get_simulation_time();
    void physics(number_t dtime);

    number_t derivative_x(function, number_t x, number_t y);
    number_t derivative_y(function, number_t x, number_t y);

    point get_difference_default(unsigned long long int pt);
    unsigned long long int get_points_N();

    static vect get_color(vect velocity);
};

#endif // IMPACT_H
