#include <QtGui/QApplication>
#include "draw.h"
#include <vect.h>
#include <math.h>

f_result f1(number_t x, number_t z)
{
    f_result res;
    res.color = Draw::get_color(vect(x, x + z, z));
    number_t r = sqrt(x * x + z * z) / 2;
    res.z = sin(r) * 5;
    return(res);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Draw w;

    w.set_gravity(vect(0, -0.1, 0));
    w.set_dt(0.05);
    w.set_dt_for_views(1);
    w.set_use_gravity_n2(false);
    w.set_use_gravitomagnetism_force(false);
    w.set_use_gravitomagnetism_torque(false);

    w.add_function(f1);
    w.firework(vect(0, 1.5, 0), 1, 1, vect(0, -1, 0), 0, 200);

    w.ftl();
    w.show();
    return a.exec();
}

