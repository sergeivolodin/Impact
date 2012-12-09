#include <stdio.h>
#include <math.h>
#include "DEs.h"

void DEprintInfo();
void DEinit();
void DEprint();
void DEstep();

//#define DEBUG 1
#undef DEBUG

double A = 0.007, B = 0.005, C = 0.003, p = 0.5, q = 5, r = 0, q0;
double dt = 1e-4, t = 0, minTime = 1, epsCheck = 0.0015;

long long N = 0;
const long long NC = 10;

double dq, dp, dr;

void DEStep()
{
    dp = (B - C) / A * q * r * dt;
    dq = (C - A) / B * r * p * dt;
    dr = (A - B) / C * p * q * dt;


    p += dp;
    q += dq;
    r += dr;

    t += dt;

    N++;
}

int DECheck()
{
    if(q > 0 && dq < 0 && (fabs(dq) / dt / q0 < epsCheck) && t > minTime)
    {
        #ifdef DEBUG
            printf("%lf\n", t);
        #endif
        return(0);
    }
    return(1);
}

void DEPrintInfo()
{
    printf("(ABC)\t%lf\t%lf\t%lf\n", A, B, C);
    printf("(pqr)\t%lf\t%lf\t%lf\n", p, q, r);
    printf("dt\t%lf\n", dt);
    printf("time\t%lf\n", t);
}

void DEPrint()
{
    printf("(pqrt)\t%lf\t%lf\t%lf\t%lf\n", p, q, r, t);
}

void DEInit()
{
    t = 0;
    N = 0;
    q0 = q;
}

double DEGet()
{
    DEInit();
    for(; DECheck();)
        DEStep();
    return(t);
}

#ifdef DEBUG

int main()
{
    DEInit();
    DEPrintInfo();

    for(; DECheck();)
    {
        DEStep();
        if(!(N % NC)) DEPrint();
    }

    return(0);
}

#endif
#ifndef DEBUG

int main()
{
    DEInit();
    scanf("%lf", &A);
    scanf("%lf", &B);
    scanf("%lf", &C);
    scanf("%lf", &p);
    scanf("%lf", &q);
    scanf("%lf", &r);
    scanf("%lf", &dt);

    DEPrintInfo();

    printf("%lf\n", DEGet());
    return(0);
}
#endif
