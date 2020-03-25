#ifndef BOMB_H
#define BOMB_H
#include "QPixmap"


class bomb
{
public:
    bomb();
    QPixmap pic_bomb;


    int position_x;
    int position_y;
    int type;
    float radius;
    int status;
    float complexity;
    int isfinish;

};

#endif // BOMB_H
