#include "vect.h"
#include <math.h>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;

using std::stringstream;

const number_vect_t rad_deg = 180. / M_PI;

void forward(number_vect_t f, vect* position, vect* angle)
{
    number_vect_t dx = 0, dy = 0, dz = 0;
    dx = -f * sin(angle->y);
    dz = f * cos(angle->y);

    dx *= cos(angle->x);
    dz *= cos(angle->x);
    dy = f * sin(angle->x);

    position->x += dx;
    position->y += dy;
    position->z += dz;
}

number_vect_t degrees(number_vect_t radians)
{
    return(rad_deg * radians);
}

vect impact(vect n, vect v)
{
    vect result = v;
    number_vect_t n_abs = n.abs();

    number_vect_t sc = v.x * n.x + v.y * n.y + v.z * n.z;
    sc /= n_abs;

    result.x -= (2. * sc * n.x / n_abs);
    result.y -= (2. * sc * n.y / n_abs);
    result.z -= (2. * sc * n.z / n_abs);

    return(result);
}

vect::vect()
{

}

vect::vect(number_vect_t x1, number_vect_t y1, number_vect_t z1)
{
    x = x1;
    y = y1;
    z = z1;
}

string vect::print()
{
    stringstream t_stream;
    t_stream << "x=" << x << " y=" << y << " z=" << z;
    string t_str = t_stream.str();
    return(t_str);
}

number_vect_t vect::abs_2()
{
    return((*this) * (*this));
}

number_vect_t vect::abs()
{
    return(sqrt(fabs(abs_2())));
}

vect vect::operator*=(number_vect_t t)
{
    x *= t;
    y *= t;
    z *= t;
    return(*this);
}

vect vect::operator+=(vect t)
{
    x += t.x;
    y += t.y;
    z += t.z;
    return(*this);
}

vect vect::operator /=(number_vect_t t)
{
    x /= t;
    y /= t;
    z /= t;
    return(*this);
}

vect vect::operator /=(vect t)
{
    x /= t.x;
    y /= t.y;
    z /= t.z;
    return(*this);
}

vect vect::operator+(vect t)
{
    vect t_vect = (*this);
    t_vect += t;
    return(t_vect);
}

vect vect::operator-(vect t)
{
    vect t_vect = (*this);
    t_vect -= t;
    return(t_vect);
}

vect vect::operator^=(vect t)
{
    vect n = (*this) ^ t;
    x = n.x;
    y = n.y;
    z = n.z;
    return(n);
}

vect vect::operator^(vect t)
{
    vect n(y * t.z - z * t.y, z * t.x - x * t.z, x * t.y - y * t.x);
    return(n);
}

vect vect::operator /(number_vect_t t)
{
    vect t_vect = (*this);
    t_vect /= t;
    return(t_vect);
}

vect vect::operator-=(vect t)
{
    x -= t.x;
    y -= t.y;
    z -= t.z;
    return(*this);
}

vect vect::operator*(number_vect_t t)
{
    vect t_vect = (*this);
    t_vect *= t;
    return(t_vect);
}

number_vect_t vect::operator*(vect t)
{
    return(x * t.x + y * t.y + z * t.z);
}
