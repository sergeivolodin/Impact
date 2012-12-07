#ifndef DZHANIBEKOVEFFECT_H
#define DZHANIBEKOVEFFECT_H
#include "draw.h"

class DzhanibekovEffect: public Draw
{
private:
    static const number_t a = 7, b = 5, c = 3, r = 5.9;

    static f_result ellipsoid(number_t x, number_t y);
    static f_result sphere(number_t x, number_t y);
    static f_result curve1(number_t x, number_t y);
    static f_result curve2(number_t x, number_t y);
    static f_result plane(number_t x, number_t y);
public:
    DzhanibekovEffect();
};

#endif // DZHANIBEKOVEFFECT_H
