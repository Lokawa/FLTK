#include "head.h"
#include "map.h"
#include "draw.h"
using namespace std;
vector<Point> dot;
Fl_Window win=Fl_Window(1300,750,"Square");
Poly_ *poly= new Poly_(50,75,1200,600);
Fl_Output *output=new Fl_Output(100,675,200,30," Pix Area");
Fl_Output *output2=new Fl_Output(400,675,200,30," Real Area");
Fl_Input *input1=new Fl_Input(100,35,100,30,"Scale");
Fl_Input *input2=new Fl_Input(225,35,100,30,":");
Fl_Box *map=new Fl_Box(50,75,1200,600);
bool chosen=false;
void Star_to_Draw(Fl_Widget *w,void *p)
{
    Poly_ *temp=(Poly_ *) p;
    poly->draw();
    float area=Area(dot);
    output->value(to_string(area).c_str());
    float pix=atof(input1->value());
    float real=atof(input2->value());
    if (pix!=0&&real!=0)
    {
        float real_area=area/pix/pix*real*real;
        output2->value(to_string(real_area).c_str());
    }
    else output2->value("Error");
    temp->redraw();
}
void exit(Fl_Widget *w,void *p)
{
    exit(0);
}
void choose(Fl_Widget *w,void *p)
{
    win.redraw();
    map->label("");
    Fl_File_Chooser chooser(".", "*", Fl_File_Chooser::SINGLE, "Choose a file");
    chooser.show();
    while(chooser.shown())
    {
        Fl::wait();
    }
    if (chooser.value() == nullptr)
    {
        return;
    }
    Fl_Image *map_photo=new Fl_PNG_Image(chooser.value());
    map->image(map_photo);
    map->redraw();
    if (!chosen)
    {
        chosen=true;
        poly->activate();
    }
}
void clear(Fl_Widget *w,void *p)
{
    dot.clear();
    win.redraw();
}
int main()
{
    map->label("Choose a photo of map.");
    poly->clear_active();
    Fl_Button *clear=new Fl_Button(900,35,100,30,"Clear");
    Fl_Button *exit=new Fl_Button(1100,675,100,30,"Exit");
    Fl_Button *choose=new Fl_Button(950,675,100,30,"Choose Map");
    exit->callback(::exit);
    choose->callback(::choose,(void*)map);
    clear->callback(::clear,(void*)poly);
    Fl_Button *start=new Fl_Button(1100,35,100,30,"Draw");
    start->callback(Star_to_Draw,(void*)poly);
    win.end();
    win.show();
    return Fl::run();
}

//------------------------------------------------------------------------------
