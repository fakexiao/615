#ifndef COPTER_H
#define COPTER_H
#include<Qpixmap.h>

class copter
{
public:
    copter();
    void setPosition();
    void returnback();
    void reback();
    void copter_over();
    init(int x_b,int y_b,int x_e, int y_e);
public:
//飞机资源对象
QPixmap pic_transcar;
//飞机坐标
int m_X;
int m_Y;
int up;//向上
int down;//向下
QRect m_Rect;
int reback_step1;
int reback_step2;
 int begin_x;
 int begin_y;
 int rebackflag;
 int end_x;
 int end_y;
 int ready_flag;
 int path_copter_y;
};

#endif // TRANS_CAR_H
