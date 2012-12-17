#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "math.h"

extern double a, b, theta, Dx, Dy, dx, dy;

#define max(a, b) ((a) > (b) ? (a) : (b))

struct point
{
    double x;
    double y;
};

struct parabola
{
    double a;
    double b;
    double c;
};

void init();
double dIx(double Dx, double x);
double dIy(double Dy, double y);
double Ix(double Dx);
double Iy(double Dy);
double Iz(double Dx, double Dy);
double DxMin();
double DyMin();
parabola parabolaCoeffs(point p1, point p2, point p3);
double parabolaVertex(parabola x);

#endif // FUNCTIONS_H
