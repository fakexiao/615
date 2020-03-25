#ifndef TRANS_CAR_H
#define TRANS_CAR_H
#include <Qpixmap.h>
#include "astar.h"
#include "ga_path.h"
#include <iostream>
using namespace std;
struct wayPoint
{
    int x, y; //点坐标，这里为了方便按照C++的数组来计算，x代表横排，y代表竖列
};
class trans_car
{
public:
    trans_car();
    void setPosition();
    void returnback();
    void findpath_astar(int a, int b, int c, int d);
    void findpath_ga();
    void trans_car_over();
public:
    //运输车资源对象

    QPixmap pic_tans_car;
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

#endif // TRANS_CAR_H
