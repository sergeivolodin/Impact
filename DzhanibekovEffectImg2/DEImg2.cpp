#include "DEImg2.h"
//#include "Surfaces.cpp"
#include <iostream>

using std::cout;
using std::endl;


DEImg2::DEImg2()
{

    draw_type = DRAW_QUADS;
}

void DEImg2::debug()
{
    vector<GLuint>::iterator it;
    for(it = objects[0].begin(); it != objects[0].end(); it++)
    {
        cout << (*it) << endl;
    }
}
