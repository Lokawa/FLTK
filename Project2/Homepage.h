//
// Created by DELL on 2023/12/25.
//

#ifndef PROJECT2_HOMEPAGE_H
#define PROJECT2_HOMEPAGE_H
#include "head.h"
void button1_cb(Fl_Widget *w,void *p);
void button2_cb(Fl_Widget *w,void *p);
extern Fl_Double_Window *game;
extern Fl_Double_Window *maze_window;
extern void callback(void *p);
class Homepage:public Fl_Window
{
public:
    Fl_Image *img,*img2,*img3;
    Fl_Box *box;
    Fl_Button *button1,*button2;
    Homepage(int x,int y,int w,int h,const char *l):Fl_Window(x,y,w,h,l)
    {
        img = new Fl_JPEG_Image("title.jpg");
        img=img->copy(1200,800);
        box=new Fl_Box(0,0,1200,800);
        box->image(img);
        button1 = new Fl_Button(200,250,200,100,"");
        img2=new Fl_PNG_Image("play.png");
        img2=img2->copy(200,100);
        button1->image(img2);
        button1->align(FL_ALIGN_IMAGE_BACKDROP);
        button2 = new Fl_Button(800,250,200,100,"");
        img3=new Fl_PNG_Image("exit.png");
        img3=img3->copy(200,100);
        button2->image(img3);
        button2->align(FL_ALIGN_IMAGE_BACKDROP);
        button1->callback(button1_cb,this);
        button2->callback(button2_cb,this);
    }
};
void button1_cb(Fl_Widget *w,void *p) {
    Homepage *homepage = (Homepage *) p;
    homepage->hide();
    homepage->button1->hide();
    homepage->button2->hide();
    maze_window->show();
}
void button2_cb(Fl_Widget *w,void *p)
{
    exit(0);
}
#endif //PROJECT2_HOMEPAGE_H
