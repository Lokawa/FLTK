//
// Created by DELL on 2023/12/26.
//

#ifndef PROJECT2_MAZE_H
#define PROJECT2_MAZE_H
#include "head.h"
#include<vector>
#include<ctime>
extern Fl_Double_Window *game;
extern const int dir[4][2];
extern const int X,Y,block_X,block_Y;
const int up=0,down=1,left=3,right=2;
struct block
{
    int x,y,direction;
    block(int x,int y,int direction):x(x),y(y),direction(direction){}
};
class maze:public Fl_Widget {
public:
    bool iswall[60][40];
    std::vector<block> path;
    maze() : Fl_Widget(0, 0, 1200, 800, "") {    }
    void find_wall(int x, int y)
    {
        if (x+1<=X-3 && iswall[x+1][y]) path.push_back(block(x+1,y,right));
        if (x-1>0 && iswall[x-1][y]) path.push_back(block(x-1,y,left));
        if (y+1<=Y-3 && iswall[x][y+1]) path.push_back(block(x,y+1,up));
        if (y-1>0 && iswall[x][y-1]) path.push_back(block(x,y-1,down));
    }
    void create_maze()
    {
        int x,y;
        memset(iswall,true,sizeof(iswall));
        srand(time(NULL));
        x=1;
        y=1;
        iswall[x][y]=false;
        find_wall(x,y);
        while(!path.empty())
        {
            int index=rand()%path.size();
            block temp=path[index];
            path.erase(path.begin()+index);
            x=temp.x;
            y=temp.y;
            switch (temp.direction)
            {
                case up:{y++;break;}
                case down:{y--;break;}
                case left:{x--;break;}
                case right:{x++;break;}
            }
            if(iswall[x][y])
            {
                iswall[temp.x][temp.y] = false;
                iswall[x][y] = false;
                find_wall(x, y);
            }
        }
        bool temp[60][40];
        for (int i=0;i<X;i++)
            for (int j=0;j<Y;j++)
                temp[i][j]=iswall[i][j];
        memset(iswall,true,sizeof(iswall));
        x=1;
        y=1;
        iswall[x][y]=false;
        path.clear();
        find_wall(x,y);
        while(!path.empty())
        {
            int index=rand()%path.size();
            block temp=path[index];
            path.erase(path.begin()+index);
            x=temp.x;
            y=temp.y;
            switch (temp.direction)
            {
                case up:{y++;break;}
                case down:{y--;break;}
                case left:{x--;break;}
                case right:{x++;break;}
            }
            if(iswall[x][y])
            {
                iswall[temp.x][temp.y] = false;
                iswall[x][y] = false;
                find_wall(x,y);
            }
        }
        for (int i=0;i<X;i++)
            for (int j=0;j<Y;j++)
                if (!temp[i][j])
                    iswall[i][j]=false;
     /*   for (int i=0;i<5;i++)
        {
            int x=rand()%(X-2)+1;
            int y=rand()%(Y-2)+1;
            while (iswall[x][y])
            {
                x=rand()%(X-2)+1;
                y=rand()%(Y-2)+1;
            }
            for (int j=0;j<4;j++)
            {
                int new_x,new_y;
                new_x=x+dir[j][0];
                new_y=y+dir[j][1];
                bool f=false;
                while (iswall[new_x][new_y] && new_x>0 && new_x<X-1 && new_y>0 && new_y<Y-1)
                {
                    if (!iswall[new_x+dir[j][0]][new_y+dir[j][1]])
                    {
                        f=true;
                        break;
                    }
                    new_x+=dir[j][0];
                    new_y+=dir[j][1];
                }
                if (f)
                {
                    new_x=x+dir[j][0];
                    new_y=y+dir[j][1];
                    while (iswall[new_x][new_y])
                    {
                        iswall[new_x][new_y]=false;
                        new_x+=dir[j][0];
                        new_y+=dir[j][1];
                    }
                    break;
                }
            }
        }*/
        /*for (int i=0;i<X;i++)
            for (int j=0;j<Y;j++)
            {
                bool f= false;
                if (iswall[i][j])
                {
                    if (i+1<X && iswall[i+1][j]) f=true;
                    if (i-1>0 && iswall[i-1][j]) f=true;
                    if (j+1<Y && iswall[i][j+1]) f=true;
                    if (j-1>0 && iswall[i][j-1]) f=true;
                    if (i+1<X && j+1<Y && iswall[i+1][j+1]) f=true;
                    if (i-1>0 && j-1>0 && iswall[i-1][j-1]) f=true;
                    if (i+1<X && j-1>0 && iswall[i+1][j-1]) f=true;
                    if (i-1>0 && j+1<Y && iswall[i-1][j+1]) f=true;
                    if (!f) iswall[i][j]=false;
                }
            }*/
        draw();
    }
    void draw()
    {
        for (int i = 0; i < X; i++)
        {
            iswall[i][0] = true;
            iswall[i][Y - 1] = true;
        }
        for (int i = 0; i < Y; i++)
        {
            iswall[0][i] = true;
            iswall[X - 1][i] = true;
        }
        for (int i = 0; i < X; i++)
        {
            for (int j = 0; j < X; j++)
            {
                if (iswall[i][j])
                {
                    fl_color(FL_WHITE);
                    fl_rectf(i * block_X, j * block_Y, block_X, block_Y);
                } else
                {
                    fl_color(FL_DARK_BLUE);
                    fl_rectf(i * block_X, j * block_Y, block_X, block_Y);
                }
            }
        }
    }

};
#endif //PROJECT2_MAZE_H
