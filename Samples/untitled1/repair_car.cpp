#include "repair_car.h"
using namespace std;
extern vector<vector<int>>  maze;

extern int obs_x[20];
extern int obs_y[20];

repair_car::repair_car()
{
    pic_repair_car.load(":/new/prefix1/img/wujiao.png");
    m_X = 1;
    m_Y = 2;

}

void repair_car::findpath_astar(int a,int b,int c,int d)
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


void repair_car::findpath_ga()
{
   count=0;
   for(count=0;count<gapath.min_path.size();count++)
   {

    pathpoint[count].y=(gapath.min_path[count])% 60 ;
    pathpoint[count].x=1+gapath.min_path[count]/60;

   }
}

void repair_car::trans_car_over()
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
