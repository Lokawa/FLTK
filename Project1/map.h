//
// Created by DELL on 2023/12/25.
//

#ifndef UNTITLED_MAP_H
#define UNTITLED_MAP_H
#include "head.h"
#include "Draw.h"
extern vector<Point> dot;
class Poly_:public Fl_Box
{
public:
    Poly_(int x,int y,int w,int h,const char *l=0):Fl_Box(x,y,w,h,l)
    {}
    Poly_(Poly_ &m): Fl_Box(m.x(),m.y(),m.y(),m.w(),m.label())
    {    }
    int handle(int e) override
    {
        if (e==FL_RELEASE)
        {
            int x=Fl::event_x();
            int y=Fl::event_y();
            fl_color(FL_RED);
            fl_circle(x,y,4);
            fl_pie(x-4,y-4,8,8,0,360);
            dot.push_back(Point(x,y));
        }
        return Fl_Widget::handle(e);
    }
    void draw()
    {
        if (dot.size()!=0)
        {
            fl_color(FL_RED);
            fl_line_style(FL_SOLID,3);
            for (int i=0;i<dot.size()-1;i++)
            {
                fl_line(dot[i].x,dot[i].y,dot[i+1].x,dot[i+1].y);
            }
            fl_line(dot[0].x,dot[0].y,dot[dot.size()-1].x,dot[dot.size()-1].y);
            fl_color(FL_YELLOW);
            for (int i=this->x();i<this->w()+this->x();i+=2)
            {
                for (int j=y();j<h()+y();j+=2)
                {
                    Point p(i,j);
                    if (Poly_Contain_Check(dot,p))
                    {
                        fl_point(i,j);
                    }
                }
            }
        }
    }
};
#endif //UNTITLED_MAP_H
