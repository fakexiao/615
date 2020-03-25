#ifndef STONE_H
#define STONE_H
#include "QPixmap"


class stone
{
public:
    stone();
    QPixmap pic_stone;
    QPixmap pic_tushifang;

    int position_x;
    int position_y;
    int type;
    float radius;
    int status;
    float complexity;
    int isfinish;
    int isfinish2;
};

#endif // STONE_H
