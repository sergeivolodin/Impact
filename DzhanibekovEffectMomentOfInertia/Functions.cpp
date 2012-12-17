#include "Functions.h"
#include "math.h"

double c, s;

void init()
{
    c = cos(theta);
    s = sin(theta);
}

double dIx(double Dx, double x)
{
    double P = pow(s / a, 2) + pow(c / b, 2);
    double Q = x * c * s * (1 / pow(b, 2) - 1 / pow(a, 2));
    double R = pow(x, 2) * (pow(c / a, 2) + pow(s / b, 2)) - 1;
    double y1 = (-Q + sqrt(pow(Q, 2) - P * R)) / P;
    double y2 = (-Q - sqrt(pow(Q, 2) - P * R)) / P;
    if(y1 != y1) return(0);
    if(y2 != y2) return(0);
    if(y1 < 0) y1 = 0;
    if(y2 < 0) y2 = 0;
    double y1_ = Dx - y1;
    double y2_ = Dx - y2;
    double dm = dx * fabs(y2_ - y1_);
    return(dm * pow(y2_ - y1_, 2) / 12. + dm * pow((y1_ + y2_) / 2., 2));
}

double dIy(double Dy, double y)
{
    double P = pow(c / a, 2) + pow(s / b, 2);
    double Q = y * c * s * (1 / pow(b, 2) - 1 / pow(a, 2));
    double R = pow(y, 2) * (pow(s / a, 2) + pow(c / b, 2)) - 1;
    double x1 = (-Q + sqrt(pow(Q, 2) - P * R)) / P;
    double x2 = (-Q - sqrt(pow(Q, 2) - P * R)) / P;
    if(x1 != x1) return(0);
    if(x2 != x2) return(0);
    double x1_ = Dy - x1;
    double x2_ = Dy - x2;
    double dm = dy * fabs(x2_ - x1_);
    return(dm * pow(x2_ - x1_, 2) / 12. + dm * pow((x1_ + x2_) / 2., 2));
}

double Ix(double Dx)
{
    double Ix = 0;
    double size = max(a, b);
    for(double x = -size; x <= size; x += dx)
        Ix += dIx(Dx, x);
    return(Ix);
}

double Iy(double Dy)
{
    double Iy = 0;
    double size = max(a, b);
    for(double y = 0; y <= size; y += dy)
        Iy += dIy(Dy, y);
    return(Iy);
}

double DxMin()
{
    point p1;
    point p2;
    point p3;

    p1.x = -a;
    p2.x = 0;
    p3.x = a;

    p1.y = Ix(p1.x);
    p2.y = Ix(p2.x);
    p3.y = Ix(p3.x);

    return(parabolaVertex(parabolaCoeffs(p1, p2, p3)));
}

double DyMin()
{
    point p1;
    point p2;
    point p3;

    p1.x = b;
    p2.x = 2 * b;
    p3.x = 3 * b;

    p1.y = Iy(p1.x);
    p2.y = Iy(p2.x);
    p3.y = Iy(p3.x);
    return(parabolaVertex(parabolaCoeffs(p1, p2, p3)));
}

parabola parabolaCoeffs(point p1, point p2, point p3)
{
    parabola res;

    double x1 = p1.x;
    double x2 = p2.x;
    double x3 = p3.x;

    double y1 = p1.y;
    double y2 = p2.y;
    double y3 = p3.y;

    res.a = (y3 - (x3 * (y2 - y1) + x2 * y1 - x1 * y2) / (x2 - x1)) / (x3 * (x3 - x1 - x2) + x1 * x2);
    res.b = (y2 - y1) / (x2 - x1) - res.a * (x1 + x2);
    res.c = (x2 * y1 - x1 * y2) / (x2 - x1) + res.a * x1 * x2;

    return(res);
}

double parabolaVertex(parabola x)
{
    return(-x.b / 2. / x.a);
}

double Iz(double Dx, double Dy)
{
    return(Ix(Dx) + Iy(Dy));
}
