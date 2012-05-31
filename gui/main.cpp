#include <QtGui/QApplication>
#include "draw.h"
#include <vect.h>
#include <math.h>

number_t f1_a(number_t x, number_t y)
{
    number_t res;

    number_t r = sqrt(x * x + y * y) / 10;

    //res = x * y / 100;
    res = 0;

    if(res == res)
    {
        if(res > 100) res = 100;
        else if(res < -100) res = -100;
    }
    return(res);
}

const number_t eps = 1E-2;

f_result f1(number_t x, number_t y)
{
    f_result res;
    res.z = f1_a(x, y);
    res.color = vect(0.5, 1, 0.1);
    float d_x = (res.z - f1_a(x + eps, y)) / eps, d_y = (res.z - f1_a(x, y + eps)) / eps;
    /*res.color.z = sqrt(pow(d_x, 2) + pow(d_y, 2));
    res.color.y = fabs(d_x) / 100;
    res.color.x = fabs(d_y) / 100;*/
    res.color = Draw::get_color(vect(x, x - y, y));
    res.color /= 8;
    return(res);
}

f_result f2(number_t x, number_t y)
{
    f_result res;
    res.color = Draw::get_color(vect(x, x + y, y));

    res.z = x * x + y * y + 50;
    res.z /= 10;

    //if(sqrt(x * x + y * y) > 8) res.z = sqrt(-1);
    //if(sqrt(x * x + y * y) < 5.5) res.z = sqrt(-1);

    return(res);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Draw w;

    w.set_track_path(true);

    number_t omega = 1E11, distance = 40, velocity = 3, dt = 0.01, mtime = 1000;
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

    w.ftl();
    w.show();
    return a.exec();
}

