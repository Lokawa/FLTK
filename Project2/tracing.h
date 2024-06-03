//
// Created by DELL on 2023/12/27.
//

#ifndef PROJECT2_TRACING_H
#define PROJECT2_TRACING_H
#include "head.h"
#include "maze.h"
#include "avatar.h"
#include "monster.h"
#include "win.h"
extern const int dir[4][2];
extern Avatar *player;
extern Monster *mon;
using namespace std;
void trace()
{
    int x=player->x;
    int y=player->y;
    int monster_x=mon->x;
    int monster_y=mon->y;
    int distance=abs(x-monster_x)+abs(y-monster_y);
    int direction=-1;
    for (int i=0;i<4;i++)
    {
        int new_x,new_y;
        new_x=monster_x+dir[i][0];
        new_y=monster_y+dir[i][1];
        if (!m->iswall[new_x][new_y])
        {
            int new_distance=abs(x-new_x)+abs(y-new_y);
            if (new_distance<=distance)
            {
                distance=new_distance;
                direction=i;
            }
        }
    }
    if (direction==-1) direction=rand()%4;
    mon->move(direction);
}
void check()
{
    if (player->x==mon->x && player->y==mon->y)
    {
        Fl::remove_timeout(callback);
        flag=false;
        Lose *lose=new Lose(300,200,600,400,"You Lose!");
        lose->show();
    }
    if (bean_num==0)
    {
        Fl::remove_timeout(callback);
        flag=false;
        Win *win=new Win(300,200,600,400,"You Win!");
        win->show();
    }
}

void best_direction(int x,int y)
{
    int monster_x=mon->x;
    int monster_y=mon->y;
    queue<pair<int,int>> q;
    q.push(make_pair(x,y));
    bool visited[X][Y];
    memset(visited,false,sizeof(visited));
    visited[x][y]=true;
    pair<int,int> pre;
    while (!q.empty())
    {
        pair<int,int> temp=q.front();
        q.pop();
        for (int i=0;i<4;i++)
        {
            int new_x,new_y;
            new_x=temp.first+dir[i][0];
            new_y=temp.second+dir[i][1];
            if (!m->iswall[new_x][new_y] && !visited[new_x][new_y])
            {
                visited[new_x][new_y]=true;
                q.push(make_pair(new_x,new_y));
                if (new_x==monster_x && new_y==monster_y)
                {
                    pre=make_pair(temp.first,temp.second);
                    break;
                }
            }
        }
    }
    if (pre.first==monster_x+1 && pre.second==monster_y) mon->move(2);
    else if (pre.first==monster_x-1 && pre.second==monster_y) mon->move(3);
    else if (pre.first==monster_x && pre.second==monster_y+1) mon->move(0);
    else if (pre.first==monster_x && pre.second==monster_y-1) mon->move(1);
    else mon->move(rand()%4);
}
#endif //PROJECT2_TRACING_H
