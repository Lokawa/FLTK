//
// Created by DELL on 2023/12/26.
//

#ifndef PROJECT2_MONSTER_H
#define PROJECT2_MONSTER_H
#include "head.h"
#include "maze.h"
extern Fl_Double_Window *game;
extern maze *m;
class Monster:public Fl_Box
{
public:
    Fl_Image *img;
    int x,y;
    Monster():Fl_Box(block_X,block_Y,block_X,block_Y,"")
    {
        img=new Fl_PNG_Image("monster.png");
        img=img->copy(block_X,block_Y);
        this->image(img);
        this->align(FL_ALIGN_IMAGE_BACKDROP);
    }
    void move(int direction)
    {
        int new_x,new_y;
        new_x=x+dir[direction][0];
        new_y=y+dir[direction][1];
        if(!m->iswall[new_x][new_y])
        {
            x=new_x;
            y=new_y;
            this->position(x*block_X,y*block_Y);
        }
        this->parent()->redraw();
    }
};
#endif //PROJECT2_MONSTER_H
