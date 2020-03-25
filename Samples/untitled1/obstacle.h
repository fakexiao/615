#ifndef OBSTACLE_H
#define OBSTACLE_H
#include<Qpixmap.h>

class obstacle
{
public:
    obstacle();
    QPixmap pic_obstacle;

    int position_x;
    int position_y;
    int type;
    float radius;
    int status;
    float complexity;
    int isfinish;
    int isfinish2;
};

#endif // OBSTANCLE_H
