#ifndef BOMB_CAR_H
#define BOMB_CAR_H
#include <Qpixmap.h>
#include "astar.h"
#include "ga_path.h"
#include <iostream>
#include "trans_car.h"
using namespace std;

class bomb_car
{
public:
     bomb_car();
     QPixmap pic_bomb_car;
     void setPosition();
     void returnback();
     void findpath_astar(int a, int b, int c, int d);
     void findpath_ga();
     void trans_car_over();
 public:

     //运输车坐标
     int m_X;
     int m_Y;
     ASTAR astar;
     GA_path gapath;
     wayPoint pathpoint[200];
     int count=0;
     list<Point *> path ;
     vector<int> task_time;
     vector<int> task_locking;
     int task_flag;
     bool disappear;
 private:
     int car_efficiency;//车辆效率
     float car_velcity;//车辆速度
     float oil_consume;//油耗
     float holding_time_h;//续航时间
     float car_lunjv;//车辆轮距
     float car_length;//车辆长度
     float turn_radius;//转弯半径
};

#endif // BOMB_CAR_H



