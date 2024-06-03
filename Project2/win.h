//
// Created by DELL on 2023/12/26.
//

#ifndef PROJECT2_WIN_H
#define PROJECT2_WIN_H
#include "head.h"
#include "maze.h"
#include "Homepage.h"
#include "Avatar.h"
#include "monster.h"

extern Fl_Double_Window *maze_window;
extern Fl_Double_Window *game;
extern Homepage *homepage;
extern maze  *m;
extern Avatar *player;
extern Monster *mon;
extern Fl_Box *bean[60][40];
extern bool eaten[60][40];
extern int bean_num;
extern bool flag;
extern int level;
void renew()
{
    flag=false;
    m->create_maze();
    player->x=1;
    player->y=1;
    player->position(player->x*block_X,player->y*block_Y);
    mon->x=rand()%X;
    mon->y=rand()%Y;
    while (m->iswall[mon->x][mon->y])
    {
        mon->x=rand()%X;
        mon->y=rand()%Y;
    }
    mon->position(mon->x*block_X,mon->y*block_Y);
    bean_num=0;
    for (int i=0;i<X;i++)
        for (int j=0;j<Y;j++)
        {
            eaten[i][j]=!m->iswall[i][j];
            bean[i][j]->hide();
            if (!m->iswall[i][j])
            {
                bean[i][j]->show();
                bean_num++;
            }
        }
    bean[1][1]->hide();
}
class Win:public Fl_Window
{
public:
    Fl_Box *box;
    Fl_Button *button;
    Win(int x,int y,int w,int h,const char *l):Fl_Window(x,y,w,h,"Congratulations!")
    {
        box=new Fl_Box(0,0,600,400,"");
        Fl_Image *img=new Fl_JPEG_Image("win.jpg");
        img=img->copy(600,400);
        box->image(img);
        button=new Fl_Button(230,300,140,70,"");
        Fl_Image *img2=new Fl_PNG_Image("back1.png");
        img2=img2->copy(140,70);
        button->image(img2);
        button->align(FL_ALIGN_IMAGE_BACKDROP);
        button->callback(button_cb,this);
       // this->clear_border();
    }
    static void button_cb(Fl_Widget *w,void *p)
    {
        Win *win=(Win *)p;
        win->hide();
        renew();
        maze_window->hide();
        homepage->show();
        homepage->button1->show();
        homepage->button2->show();
        level=1;
        w->parent()->redraw();
    }
};
class Lose:public Fl_Window
{
public:
    Fl_Box *box;
    Fl_Button *button;
    Lose(int x,int y,int w,int h,const char *l):Fl_Window(x,y,w,h,"Gotcha~")
    {
        box=new Fl_Box(0,0,600,400,"");
        Fl_Image *img=new Fl_JPEG_Image("lose.jpg");
        img=img->copy(600,400);
        box->image(img);
        box->align(FL_ALIGN_IMAGE_BACKDROP);
        button=new Fl_Button(230,300,140,70,"");
        button->box(FL_NO_BOX);
        Fl_Image *img2=new Fl_PNG_Image("back2.png");
        img2=img2->copy(140,70);
        button->image(img2);
        button->align(FL_ALIGN_IMAGE_BACKDROP);
        button->callback(button_cb,this);
      //  this->clear_border();
    }
    static void button_cb(Fl_Widget *w,void *p)
    {
        Lose *lose=(Lose *)p;
        lose->hide();
        renew();
        maze_window->hide();
        homepage->show();
        homepage->button1->show();
        homepage->button2->show();
        level=1;
        w->parent()->redraw();
    }
};
#endif //PROJECT2_WIN_H
