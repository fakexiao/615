#include "bomb_car.h"
using namespace std;
extern vector<vector<int>>  maze;

extern int bomb_x[20];
extern int bomb_y[20];

bomb_car::bomb_car()
{
    pic_bomb_car.load(":/new/prefix1/img/sanjiao.png");
    m_X = 1;
    m_Y = 2;

}



void bomb_car::findpath_astar(int a,int b,int c,int d)
{
    count=0;
    for (int i=0;i<50;i++)
    {
        pathpoint[i].x=0;
        pathpoint[i].y=0;
    }
   Point start(a, b);
   Point end(c, d);
   path = astar.GetPath(start, end, false);
   for (auto &p : path)
   {
       pathpoint[count].y=p->x;
       pathpoint[count].x=p->y;
       count++;
}
}


void bomb_car::findpath_ga()
{
   count=0;
   for(count=0;count<gapath.min_path.size();count++)
   {

    pathpoint[count].y=(gapath.min_path[count])% 60 ;
    pathpoint[count].x=1+gapath.min_path[count]/60;

   }
}

void bomb_car::trans_car_over()
{

    m_X = 1;
    m_Y = 2;
    for(auto &p:path)
    {
        if(p!=nullptr)
            p=nullptr;
    }
    path.clear();
    for (int i=0;i<50;i++)
    {
        pathpoint[i].x=0;
        pathpoint[i].y=0;
    }

}

