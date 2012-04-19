#ifndef VECT_H
#define VECT_H

#include <vector>
#include <string>

using std::vector;
using std::string;
typedef long double number_vect_t;

class vect
{
public:
    number_vect_t x;
    number_vect_t y;
    number_vect_t z;

    vect();
    vect(number_vect_t x1, number_vect_t y1, number_vect_t z1);
    string print();
    number_vect_t abs_2();
    number_vect_t abs();
    vect operator+(vect t);
    vect operator*=(number_vect_t t);
    vect operator+=(vect t);
    vect operator-=(vect t);
    vect operator*(number_vect_t t);
    number_vect_t operator*(vect t);
};

struct f_result
{
    number_vect_t z;
    vect color;
};

struct point
{
    vect position;
    vect velocity;
    vect acceleration;
    number_vect_t mass;

    vect color;
    vector<short int> states;
};

void forward(number_vect_t f, vect* position, vect* angle);
number_vect_t degrees(number_vect_t radians);
vect impact(vect n, vect v);

#endif // VECT_H
