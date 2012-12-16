#include "draw.h"

#ifndef SURFACES_H
#define SURFACES_H

const number_t a = 7, b = 5, c = 3, r = 4.5;

f_result ellipsoid(number_t x, number_t y);
f_result sphere(number_t x, number_t y, void* r);
f_result curve1(number_t x, number_t y, void *g);
f_result curve2(number_t x, number_t y, void *g);
f_result plane(number_t x, number_t y);

struct curve_param
{
    number_t r;
    vect color;
};

#endif // SURFACES_H
