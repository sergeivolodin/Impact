#ifndef IMPACT_H
#define IMPACT_H

#include "vect.h"
#include <string>
#include <vector>

using std::vector;
using std::pair;
using std::string;

typedef long double number_t;

class Impact
{
friend class Draw;
private:
    //physics
    bool precise_impact;
    bool use_gravity;
    bool use_gravity_points;
    bool use_gravity_n2;
    bool track_path;
    bool use_gravitomagnetism_force;
    bool use_gravitomagnetism_torque;
    number_t derivative_eps;
    number_t time;
    unsigned int impact_max_iterations;

    //world
    number_t dt;
    number_t M; //max_coord
    vect gravity;

    number_t G;
    number_t c;

    vector<point> mypoints;
    vector<point> mygravitypoints;
    vector<point> mypoints_defaults;
    vector<f_result (*)(number_t, number_t)> myfunctions;

    static const int DIFFERENCE_NAN = 2;

public:
    Impact();

    void add_function(f_result(*f)(number_t, number_t));
    void add_point(vect position, vect velocity, vect color, number_t mass, vect angular_velocity, number_t moment_of_inertia);
    void add_gravity_point(vect position, number_t mass);
    void add_points(f_result(*f)(number_t, number_t), number_t M, number_t step, vect velocity, number_t mass, vect angular_velocity, number_t moment_of_inertia);
    void firework(vect position, number_t velocity, number_t mass, vect angular_velocity, number_t moment_of_inertia, unsigned int N);

    void set_gravity(vect x);
    void set_dt(number_t x);
    void set_use_gravity_n2(bool x);
    void set_use_gravitomagnetism_force(bool x);
    void set_use_gravitomagnetism_torque(bool x);
    string print_points();
    string print_point(point& pt, bool print_acceleration);

    number_t get_simulation_time();
    void physics(number_t dtime);

    number_t derivative_x(f_result(*f)(number_t, number_t), number_t x, number_t y);
    number_t derivative_y(f_result(*f)(number_t, number_t), number_t x, number_t y);

    point get_difference_default(unsigned long long int pt);
    unsigned long long int get_points_N();
protected:
    void points_defaults();

    int difference(vect coords, f_result(*f)(number_t, number_t));
    vect tangent(f_result(*f)(number_t, number_t), number_t x, number_t y);

    void physics_set_acceleration(point& pt);
    void physics_move(point& pt, number_t dtime);
    vect physics_gravity(point& p1, point& p2);
    pair<vect, vect> physics_gravitomagnetism(point& p1, point& p2);

    vect get_color(vect velocity);
};

#endif // IMPACT_H
