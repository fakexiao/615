#include "copter.h"
extern int copter_num;
extern int copter_check2;
extern int copter_check1;
copter::copter()
{
    pic_transcar.load(":/new/prefix1/img/wurenji.png");

    up=0;
    down=1;

    rebackflag=0;
    ready_flag=0;
    reback_step1=0;
    reback_step2=0;
}

copter::init(int x_b,int y_b,int x_e, int y_e)
{
    begin_x = x_b;
    begin_y = y_b;

    end_x = x_e;
    end_y = y_e;

}


void copter::setPosition()
{

    if(ready_flag==0)
    {

        if(m_X==begin_x&&m_Y==begin_y)
            ready_flag=1;
        if(m_X<begin_x)m_X=m_X+1;
        if(m_Y<begin_y)m_Y=m_Y+1;

    }

    if(m_X == end_x && m_Y == end_y)
        rebackflag=1;

    if (rebackflag!=1&&ready_flag)
    {
        if (down)
        {
            m_Y=m_Y+1;
            m_X=m_X;
            if (m_Y>58)
            {
                down=0;
                up=1;
                m_Y=m_Y;
                m_X=m_X+1;
            }
        }

        else if (up)
        {

            m_Y=m_Y-1;
            m_X=m_X;
            if (m_Y<=0)
            {
                down=1;
                up=0;
                m_Y=m_Y;
                m_X=m_X+1;
            }

        }

    }
    if(rebackflag==1)
        reback();
}

void copter::reback()
{

    if(reback_step1==0)
    {
        if(m_Y ==path_copter_y)
            reback_step1=1;

        if(m_Y > path_copter_y)
        {

            m_Y = m_Y - 1;
        }

        if(m_Y <path_copter_y )
        {

            m_Y = m_Y + 1;
        }

    }
    if(copter_check1==copter_num)
    {

          if(m_X == 0&&m_Y ==path_copter_y)
              reback_step2=1;

        if(m_X > 0&&m_Y ==path_copter_y)
        {
            m_X = m_X - 1;
        }
    }
    if(copter_check2==copter_num)
        if(m_Y > 0)
        {

            m_Y = m_Y - 1;
        }

}


void copter::copter_over()
{
    m_X = 0;
    m_Y = 0;
    up = 0;
    down = 1;
    rebackflag = 0;
}

