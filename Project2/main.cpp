#include "head.h"
#include "Homepage.h"
#include "maze.h"
#include "Avatar.h"
#include "win.h"
#include "monster.h"
#include "tracing.h"

Fl_Double_Window *game = new Fl_Double_Window(0,0,1200,800,"Pacman(JOJO ver.)");
Fl_Double_Window *maze_window = new Fl_Double_Window(0,0,1200,800,"");
maze *m=new maze();
Avatar *player=new Avatar();
Homepage *homepage = new Homepage(0,0,1200,800,"");
const int dir[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
const int block_X=50,block_Y=50,X=24,Y=16;
bool eaten[60][40];
Fl_Box *bean[60][40];
int bean_num=0;
Fl_Image *bean_img=new Fl_PNG_Image("bean.png");
Monster *mon=new Monster();
Fl_Menu_Bar *menu=new Fl_Menu_Bar(0,0,1200,30);
bool flag=false;
int level=1;

void callback(void *)
{
    switch (level)
    {
        case 1:Fl::repeat_timeout(0.5, callback);break;
        case 2:Fl::repeat_timeout(0.3, callback);break;
        case 3:Fl::repeat_timeout(0.1, callback);break;
    }
  //  Fl::repeat_timeout(0.5, callback);
  //  trace();
    best_direction(player->x,player->y);
    check();
}
void choose_avatar(Fl_Widget *w,void *p)
{
    const char* l=fl_file_chooser("Choose your avatar","*.png","");
    if (l!=NULL)
    {
        player->img=new Fl_PNG_Image(l);
        player->img=player->img->copy(block_X,block_Y);
        player->image(player->img);
        player->align(FL_ALIGN_IMAGE_BACKDROP);
    }
    player->redraw();
    player->parent()->redraw();
}
void choose_monster(Fl_Widget *w,void *p)
{
    const char* l=fl_file_chooser("Choose your monster","*.png","");
    if (l!=NULL)
    {
        mon->img=new Fl_PNG_Image(l);
        mon->img=mon->img->copy(block_X,block_Y);
        mon->image(mon->img);
        mon->align(FL_ALIGN_IMAGE_BACKDROP);
    }
    mon->redraw();
    mon->parent()->redraw();
}

void shrink(Fl_Widget *w,void *p)
{
    Fl_Double_Window *win=(Fl_Double_Window *)p;
    int ww=win->w()-10;
    int hh=win->h()-10;
    win->size(ww,hh);
    win->redraw();
}
void grow(Fl_Widget *w,void *p)
{
    Fl_Double_Window *win=(Fl_Double_Window *)p;
    int ww=win->w()+10;
    int hh=win->h()+10;
    win->size(ww,hh);
    win->redraw();
}

int main() {
    bean_img->copy(50,50);
    game->begin();
    game->add(homepage);
    homepage->clear_border();
    //Homepage settings
    game->add(maze_window);
    maze_window->begin();
    maze_window->add(m);
    m->create_maze();
    bean_num=0;
    for (int i=0;i<X;i++)
        for (int j=0;j<Y;j++)
        {
            eaten[i][j]=!m->iswall[i][j];
            bean[i][j]=new Fl_Box(i*block_X,j*block_Y,block_X,block_Y,"");
            bean[i][j]->image(bean_img);
            bean[i][j]->align(FL_ALIGN_CENTER);
            bean[i][j]->hide();
            maze_window->add(bean[i][j]);
            if (!m->iswall[i][j])
            {
                bean[i][j]->show();
                bean_num++;
            }
        }
    bean[1][1]->hide();
    //maze and bean settings
    menu->add("Game/Start",'s',[](Fl_Widget *w,void *p){flag=true; Fl::add_timeout(0.1,callback);});
    menu->add("Game/Pause",'p',[](Fl_Widget *w,void *p){flag=false;Fl::remove_timeout(callback);});
    menu->add("Game/Resume",'r',[](Fl_Widget *w,void *p){flag=true;Fl::add_timeout(0.1,callback);});
    menu->add("Game/Quit",'q',[](Fl_Widget *w,void *p){exit(0);});
    menu->add("Settings/Level/Easy",'e',[](Fl_Widget *w,void *p){level=1;});
    menu->add("Settings/Level/Medium",'m',[](Fl_Widget *w,void *p){level=2;});
    menu->add("Settings/Level/Hard",'h',[](Fl_Widget *w,void *p){level=3;});
    menu->add("Customization/Avatar",'a',choose_avatar);
    menu->add("Customization/Monster",'m',choose_monster);
    menu->add("Windows/Shrink",'s',shrink,game);
    menu->add("Windows/Grow",'g',grow,game);
    maze_window->add(menu);
    //menu settings
    maze_window->add(player);
    int x=rand()%X,y=rand()%Y;
    while (m->iswall[x][y])
    {
        x=rand()%X;
        y=rand()%Y;
    }
    mon->x=x;
    mon->y=y;
    mon->position(x*block_X,y*block_Y);
    maze_window->add(mon);
    //avatar and monster settings
    maze_window->end();
    game->end();
    game->show();
    return Fl::run();
}