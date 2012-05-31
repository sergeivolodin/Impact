#include <iostream>
#include "impact.h"
#include <sstream>
#include <math.h>

using std::cout;
using std::cerr;
using std::stringstream;
using std::endl;

number_t omega = 1E11, distance = 40, velocity = 3, dt = 0.01, mtime = 1000;

number_t calculate()
{
    Impact w;

    w.set_gravity(vect(0, 0, 0));
    w.set_use_gravity_n2(false);
    w.set_use_gravitomagnetism_force(true);
    w.set_use_gravitomagnetism_torque(true);

    w.add_point(vect(distance / 2, 10, 0), vect(-velocity, 0, 0), vect(1, 1, 1), 1, vect(0, omega, 0), 1);
    w.add_point(vect(-distance / 2, 10, 0), vect(velocity, 0, 0), vect(1, 1, 1), 1, vect(0, omega, 0), 1);


    for(w.set_dt(dt); w.get_simulation_time() < mtime - dt; w.physics(dt));
    w.physics(mtime - w.get_simulation_time());
    for(w.set_dt(-dt); w.get_simulation_time() > dt; w.physics(-dt));
    w.physics(-w.get_simulation_time());

    unsigned long long int i, N = w.get_points_N();
    number_t sum = 0;
    for(i = 0; i < N; i++)
        sum += w.get_difference_default(i).position.abs();
    sum /= N;

    return(sum);
}

int main()
{
    number_t res;
    cout.precision(10);
    dt = 0.005;
    for(mtime = 1; mtime < 100; mtime += 1)
    {
        res = calculate();
        cout << mtime << "," << res << endl;
    }

    return(0);
}
