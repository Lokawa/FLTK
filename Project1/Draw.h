//
// Created by DELL on 2023/12/25.
//

#ifndef UNTITLED_DRAW_H
#define UNTITLED_DRAW_H
#include "head.h"
using namespace std;
extern vector<Point> dot;
bool Poly_Contain_Check(vector<Point> point,Point p)
{
    bool c=false;
    for (int i=0,j=point.size()-1;i<point.size();j=i++)
    {
        if (((point[i].y>p.y)!=(point[j].y>p.y))&&(p.x<(point[j].x-point[i].x)*(p.y-point[i].y)/(point[j].y-point[i].y)+point[i].x))
        {
            c=!c;
        }
    }
    return c;
}
double Area(vector<Point>point)
{
    double area=0;
    for (int i=0;i<point.size()-1;i++)
    {
        area+=(point[i].x*point[i+1].y-point[i+1].x*point[i].y);
    }
    area+=(point[point.size()-1].x*point[0].y-point[0].x*point[point.size()-1].y);
    return fabs(area/2);
}
#endif //UNTITLED_DRAW_H
