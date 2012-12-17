#include <math.h>
#include <iostream>
#include "Functions.h"

double a, b, theta, Dx, Dy, dx, dy, Dx0, Dy0;

using std::cout;
using std::endl;

int main()
{
    init();
    double R1 = 2.5e-3;
    double R2 = 4e-3;
    double e = 24e-3;
    double L = (e - 2 * R2) / 2;
    double h = 9e-3;
    double d1 = 2e-3;
    double v0 = h * L * d1;
    theta = M_PI / 4;

    a = L;
    b = h;

    cout << a << " " << b << endl;

    double q = 7800;

    double Iy_q = M_PI * h / 4 * (pow(R2, 4) - pow(R1, 4) + pow(h, 2) / 3 * (pow(R2, 2) - pow(R1, 2)));
    double Ix_q = Iy_q;
    double Iz_q = M_PI * h / 2 * (pow(R2, 4) - pow(R1, 4));

    double Ix_r = Ix_q * q; //parallel
    double Iy_r = Iy_q * q; //rectangular
    double Iz_r = Iz_q * q; //up


    dx = a / 10000;
    dy = b / 10000;
    Dx = -R2;
    Dy = DyMin();

    double qs = q * v0 / (M_PI * a * b / 2);

    double Ix0 = 2 * Ix(Dx) * qs;
    double Iy0 = 2 * Iy(Dy) * qs;
    double Iz0 = 2 * Iz(Dx, Dy) * qs;

    Ix_r += Iy0;
    Iy_r += Iz0;
    Iz_r += Ix0;

    cout << Ix_r << " " << Iy_r << " " << Iz_r << endl;
    
    return(0);
}
