#include <QtGui/QApplication>
#include "draw.h"
#include <vect.h>
#include <fstream>
#include <iostream>
#include <math.h>

using std::ifstream;
using std::cin;
using std::cout;
using std::endl;

//const number_t eps = 1E-2;

//number_t f1_a(number_t x, number_t y)
//{
//    number_t res;

//    number_t r = sqrt(x * x + y * y) / 10;

//    //res = x * y / 100;
//    res = 0;

//    if(res == res)
//    {
//        if(res > 100) res = 100;
//        else if(res < -100) res = -100;
//    }
//    return(res);
//}

//number_t f2_a(number_t x, number_t y)
//{
//    number_t r;

//    //r = (x * x + y * y) / 3;
//    //r = pow(x, 2) * pow(M_E, y - pow(x, 2));

////    if(fabs(x + y) > 10)
////        r = atan(pow(x, 2) - pow(y, 2)) / (x + y);
////    else r = x - y;
//    r = tan(x*y*y*y/(x*x+y*y*y*y));

//    return(r);
//}

//f_result f2(number_t x, number_t y)
//{
//    f_result res;
//    res.coordinates.z = f2_a(x, y);
//    res.color = vect(0.5, 1, 0.1);
//    //float d_x = (res.coordinates.z - f1_a(x + eps, y)) / eps, d_y = (res.coordinates.z - f1_a(x, y + eps)) / eps;
//    res.color = Draw::get_color(vect(x - y, x + y, y - x));
//    return(res);
//}

//f_result f0(number_t x, number_t y)
//{
//    f_result res;
//    res.coordinates.z = 5;
//    res.color = vect(0.5, 1, 0.1);
//    float d_x = (res.coordinates.z - f1_a(x + eps, y)) / eps, d_y = (res.coordinates.z - f1_a(x, y + eps)) / eps;
//    /*res.color.coordinates.z = sqrt(pow(d_x, 2) + pow(d_y, 2));
//    res.color.y = fabs(d_x) / 100;
//    res.color.x = fabs(d_y) / 100;*/
//    //res.color = Draw::get_color(vect(x, x - y, y));
//    //res.color /= 8;
//    return(res);
//}

//f_result f1(number_t x, number_t y)
//{
//    f_result res;
//    res.coordinates.z = 0;
//    res.color = vect(0.1, 0.1, 0.1);
//    float d_x = (res.coordinates.z - f1_a(x + eps, y)) / eps, d_y = (res.coordinates.z - f1_a(x, y + eps)) / eps;
//    /*res.color.coordinates.z = sqrt(pow(d_x, 2) + pow(d_y, 2));
//    res.color.y = fabs(d_x) / 100;
//    res.color.x = fabs(d_y) / 100;*/
//    //res.color = Draw::get_color(vect(x, x - y, y));
//    //res.color /= 8;
//    return(res);
//}

//f_result hyp(number_t x, number_t y)
//{
//    f_result res;

//    number_t a = 1, b = 10;

//    //res.coordinates.z = 0.5 * (pow(x / a, 2) - pow(y / b, 2));
//    //res.coordinates.z = 0.5 * (pow(x / a, 2) + pow(y / b, 2));
//    //res.coordinates.z = pow(pow(x, 2) - pow(y, 2), 0.5);
//    res.coordinates.z = 0.5 * (pow(x, 2) - pow(y, 2));

//    float d_x = (res.coordinates.z - f1_a(x + eps, y)) / eps, d_y = (res.coordinates.z - f1_a(x, y + eps)) / eps;
//    res.color = Draw::get_color(vect(d_x, res.coordinates.z, d_y));

//    return(res);
//}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Draw w;

    ifstream file("/home/seriy/Documents/p/git/Quadrocopter/debug/compass_calibrator/raw.csv");

    int N = 6854;

    int n1, n2, n3;
    char c;

    for(int i = 0; i < N; i++)
    {
        file >> n1 >> c >> n2 >> c >> n3;
        cout << n1 << "\t" << n2 << "\t" << n3 << endl;
        w.add_point(vect(n1, n2, n3) / 100, vect(0, 0, 0), vect(1, 0, 0), 0, vect(0, 0, 0), 0);
    }

    w.setClearColor(vect(0, 0, 0));

    w.ftl();
    w.show();
    return a.exec();
}


