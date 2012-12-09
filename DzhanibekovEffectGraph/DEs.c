#include <stdio.h>

void DEprintInfo();
void DEinit();
void DEprint();
void DEstep();

double A = 7, B = 5, C = 3, p = 0.01, q = 5, r = 0;
double dt = 1e-5, t = 0;

long long N = 0;
const long long NC = 10;

double dq, dp, dr;

void DEstep()
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

void DEprintInfo()
{
    printf("(ABC)\t%f\t%f\t%f\n", A, B, C);
    printf("(pqr)\t%f\t%f\t%f\n", p, q, r);
    printf("dt\t", dt);
    printf("time\t", t);
}

void DEprint()
{
    printf("(pqrt)\t%f\t%f\t%f\t%f\n", p, q, r, t);
}

void DEinit()
{
    t = 0;
    N = 0;
}

int main()
{
    DEinit();
    DEprintInfo();

    for(; ;)
    {
        DEstep();
        if(!(N % NC)) DEprint();
    }

    return(0);
}
