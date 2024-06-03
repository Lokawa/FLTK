//
// Created by DELL on 2023/12/26.
//

#ifndef PROJECT2_AVATAR_H
#define PROJECT2_AVATAR_H
#include "head.h"
#include "maze.h"

extern maze *m;
extern Fl_Double_Window *maze_window;
extern const int dir[4][2];
extern Fl_Box *bean[60][40];
extern bool eaten[60][40];
extern int bean_num;
extern bool flag;

class Avatar:public Fl_Box
{
    friend class maze;
public:
    Fl_Image *img;
    int x,y,score;
    Avatar():Fl_Box(block_X,block_Y,block_X,block_Y,"")
    {
        this->x=1;
        this->y=1;
        img=new Fl_PNG_Image("avatar.png");
        img=img->copy(block_X,block_Y);
        this->image(img);
        this->align(FL_ALIGN_IMAGE_BACKDROP);
    }
    int handle(int event)
    {
        int direction=-1;
        switch (event)
        {
            case FL_KEYUP:
            {
                switch (Fl::event_key())
                {
                    case FL_Up:{direction=1;break;}
                    case FL_Down:{direction=0;break;}
                    case FL_Left:{direction=3;break;}
                    case FL_Right:{direction=2;break;}
                }
                if (direction!=-1 && flag)
                {
                    int new_x,new_y;
                    new_x=x+dir[direction][0];
                    new_y=y+dir[direction][1];
                    if(!m->iswall[new_x][new_y])
                    {
                        x=new_x;
                        y=new_y;
                        this->position(x*block_X,y*block_Y);
                        if (eaten[x][y])
                        {
                            eaten[x][y]=false;
                            bean[x][y]->hide();
                            bean_num--;
                        }
                    }
                    this->parent()->redraw();
                }
                break;
            }

        }
        return 1;
    }
};
#endif //PROJECT2_AVATAR_H
