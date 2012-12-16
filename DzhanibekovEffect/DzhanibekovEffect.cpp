#include "DzhanibekovEffect.h"
//#include "Surfaces.cpp"
#include <iostream>

using std::cout;
using std::endl;


DzhanibekovEffect::DzhanibekovEffect()
{
//    function p, e, s, c1, c2;

//    p.first = (void*) plane;
//    e.first = (void*) ellipsoid;
//    s.first = (void*) sphere;
//    c1.first = (void*) curve1;
//    c2.first = (void*) curve2;

//    p.second.type = function_info::T_COORDINATE;
//    p.second.xmin = -20;
//    p.second.xmax = 20;
//    p.second.xstep = 0.05;
//    p.second.ymin = -20;
//    p.second.ymax = 20;
//    p.second.ystep = 0.05;

//    e.second = p.second;
//    e.second.type = function_info::T_PARAMETRIC;
//    e.second.xmin = -M_PI / 2;
//    e.second.xmax =  M_PI / 2;
//    e.second.ymin = -M_PI;
//    e.second.ymax =  M_PI;

//    s.second = e.second;
//    c1.second = e.second;
//    c1.second.xmin = 0;
//    c1.second.xmax = 0;
//    c1.second.xstep = 1;
//    c1.second.ymin = 0;
//    c1.second.ymax = 10 * M_PI;
//    c1.second.ystep = 2 * M_PI / 10000;
//    c2.second = c1.second;



//    //add_function(p);
//    //ftl_f(e);
//    add_function(e);
////    ftl_f(s);
////    ftl_f(c1);
////    ftl_f(c2);


}

void DzhanibekovEffect::debug()
{
    vector<GLuint>::iterator it;
    for(it = objects[0].begin(); it != objects[0].end(); it++)
    {
        cout << (*it) << endl;
    }
}
