#include "gridmap.h"
#include <QTime>
#include <QPushButton>
#include <QPainter>
#include <QDebug>
#include <QtCore/qmath.h>
#include <QApplication>

#include <set>
#include <iostream>
#include <math.h>


vector<vector<int> >  maze;
int num1[20] = {0};
int numclear[20] = {0};
int numbomb[20] = {0};
int numrepair[20] = {0};
int numrepair2[20] = {0};
int num1back[20] = {0};
int numrepairback[20] = {0};
int numrepairback2[20] = {0};
int numclearback[20] = {0};
int numbombback[20] = {0};
int num1return[20] = {0};
int copter_check1;
int copter_check2;
int numclearreturn[20] = {0};
int numbombreturn[20] = {0};
int numrepairreturn[20] = {0};
int numcopterreturn[20] = {0};
int num2 = 0;
int obs_count[20] = {0};
int bomb_count[20] = {0};
int stone_count[20] = {0};
int route_flag;
int copter_flag[20];
int copter_path[20]={0,3,6,9,12,15,18,21,24,27,30,33,36,39,42,45,48,51,54,57};
int copter_flag2;
int repair_to_home[20] = {0};
int copter_last_m_Y[20] = {0};
int copter_last_m_X[20] = {0};
int repair_need = 0;
int repair_to_clear = 0;
float t_trans_task_average;
float time_trans_limit_up;
float time_trans_limit_down;
float t_clear_task_average;
float time_clear_limit_up;
float time_clear_limit_down;
float t_bomb_task_average;
float time_bomb_limit_up;
float time_bomb_limit_down;
float t_repair_task_average;
float time_repair_limit_up;
float time_repair_limit_down;
float t_repair_task_average2;
float time_repair_limit_up2;
float time_repair_limit_down2;
int trans_time[20] = {0};
int repair_time[20] = {0};
int clear_time[20] = {0};
int bomb_time[20] = {0};
extern int clearfinish[20];
extern int repairfinish[20];
extern int bombfinish[20];
extern int obs_x[20];
extern int obs_y[20];
extern int obs_num;
extern int stone_x[20];
extern int stone_y[20];
extern int bomb_x[20];
extern int bomb_y[20];
extern int obs_comp[20];
extern int stone_comp[20];
extern int bomb_comp[20];
extern int trans_num[20];
extern int repair_num[20];
extern int bomb_num[20];
extern int clear_num[20];

extern int trans_velo[20];
extern int repair_velo[20];
extern int clear_velo[20];
extern int bomb_velo[20];

extern float trans_effi_sum;
extern float bomb_effi_sum;
extern float clear_effi_sum;
extern float repair_effi_sum;
extern float trans_effi[20];
extern float bomb_effi[20];
extern float clear_effi[20];
extern float repair_effi[20];

int trans_start;
int repair_to_clear_start;
int copter_repeat;
int obstacle_num = 0;
int stone_see_num = 0;
int bomb_see_num = 0;
extern int trans_car_num;
extern int clear_car_num;
extern int bomb_car_num;
extern int copter_num;
extern int repair_car_num;
extern int veh_num;
set<int> obsSet;
set<int>::iterator it;
int obstable = 0;
int obs_table[20] = {0};
set<int> stoneSet;
int stonetable = 0;
int stone_table[20] = {0};
set<int> bombSet;
int bombtable = 0;
int bomb_table[20] = {0};

int startAngle[20] = {0};
int startAngle1[20] = {0};
int startAngle2[20] = {0};
int startAngle3[20] = {0};
int step1[20]={0};
int step2[20]={0};
bool show_flag=false;

extern int trans_crash;
extern int bomb_crash;
extern int repair_crash;
extern int clear_crash;
extern int trans_crash_flag;
extern int bomb_crash_flag;
extern int clear_crash_flag;
extern int repair_crash_flag;

gridmap::gridmap(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("Gridmap"));
    this->setFixedSize(1920,1080);//设置位置和大小
    this->setWindowOpacity(1);//设置透明度


    QToolButton *toolButton = new QToolButton(this); //新建toolButton
    toolButton->setText("TSAK"); //设置内容
    toolButton->setPopupMode(QToolButton::MenuButtonPopup); //设置模式 必须
    QMenu * m = new QMenu(this); //创建菜单
    QAction *a1 = m->addAction("START");
    QAction *a2 = m->addAction("STOP");
    QAction *a3 = m->addAction("OVER");
    QAction *a4 = m->addAction("EMERGENCY");
    QAction *a5 = m->addAction("SHOW_LINE");
    toolButton->setMenu(m); //将菜单添加到toolButton中


    //    QToolButton *toolButton2 = new QToolButton(this); //新建toolButton
    //    toolButton2->setText("ROUTE"); //设置内容
    //    toolButton2->setPopupMode(QToolButton::MenuButtonPopup); //设置模式 必须
    //    QMenu * n = new QMenu(this); //创建菜单
    //    QAction *b1 = n->addAction("STAR");
    //    QAction *b2 = n->addAction("GA");
    //    toolButton2->setMenu(n); //将菜单添加到toolButton中
    //    QToolBar * toolBar = new QToolBar(this); //添加工具栏
    //    toolBar->addWidget(toolButton); //将toolButtn添加到工具栏中
    //    toolBar->addWidget(toolButton2); //将toolButtn添加到工具栏中

    factor = 1.0;

    m_timer = new QTimer(this);
    e_timer = new QTimer(this);
    h_timer = new QTimer(this);

    connect(a1, &QAction::triggered,
            [=]()
    {
        Start_task();

    });

    connect(a2, &QAction::triggered,
            [=]()
    {
        Stop_task();

    });

    connect(a3, &QAction::triggered,
            [=]()
    {
        Over_task();
        update();

    });

    connect(a4, &QAction::triggered,
            [=]()
    {
        Emr_return_task();

    });

    connect(a5, &QAction::triggered,
            [=]()
    {
        show_flag=!show_flag;

    });

    //    connect(b1, &QAction::triggered,
    //            [=]()
    //    {

    //        route_flag = 1;

    //    });

    //    connect(b2, &QAction::triggered,
    //            [=]()
    //    {

    //        route_flag = 1;

    //    });

    begin_run();





}

void gridmap::Start_task()
{
    e_timer->stop();
    sleep(100);
    m_timer->start(100);
    for (int i = 0; i < 20; i++)
    {
        num1return[i] = 0;
        numbombreturn[i] = 0;
        numclearreturn[i] = 0;
        startAngle[i] = 0;
        startAngle1[i] = 1440;
        startAngle2[i] = 1440;
        startAngle3[i] = 0;
    }
    copter_flag2 = 0;
    for(int i=0;i<20;i++)
    {step1[i]=0;
        step2[i]=0;
    }
    if(copter_num>0)
    {
        for(int i=0;i<copter_num;i++)
        {

            if(copter_flag[i]!= 1)
            {


                task_plan1.copter_team[i].init((80/copter_num)*i,0,(80/copter_num)*(i+1)-1,59);


                task_plan1.copter_team[copter_num-1].init((80/copter_num)*(copter_num-1),0,79,59);
            }
        }
    }
    for(int i=0;i<copter_num;i++)
    {
        task_plan1.copter_team[i].path_copter_y=copter_path[i];
    }



}

void gridmap::Stop_task()
{
    e_timer->stop();
    h_timer->stop();
    m_timer->stop();


}

void gridmap::Over_task()
{
    trans_start = 0;
    repair_to_clear_start = 0;
    obs_num = 0;
    copter_repeat = 0;
    repair_need = 0;


    num2 = 0;
    trans_car_num = 0;
    obstacle_num = 0;
    clear_car_num = 0;
    stone_see_num = 0;
    bomb_car_num = 0;
    bomb_see_num = 0;
    obstable = 0;
    bombtable = 0;
    stonetable = 0;
    trans_effi_sum = 0;
    bomb_effi_sum = 0;
    repair_effi_sum = 0;
    clear_effi_sum = 0;
    copter_num = 0;
    veh_num = 0;
    for (int i = 0; i < 20; i++)
    {
        num1[i] = 0;
        num1back[i] = 0;
        num1return[i] = 0;
        numrepair[i] = 0;
        numrepair2[i] = 0;
        numrepairback[i] = 0;
        numrepairback2[i] = 0;
        numrepairreturn[i] = 0;
        numclear[i] = 0;
        numclearback[i] = 0;
        numclearreturn[i] = 0;
        numbomb[i] = 0;
        numbombback[i] = 0;
        numbombreturn[i] = 0;
        obs_count[i] = 0;
        bomb_count[i] = 0;
        stone_count[i] = 0;
        obs_x[i] = 0;
        obs_y[i] = 0;
        stone_x[i] = 0;
        stone_y[i] = 0;
        bomb_x[i] = 0;
        bomb_y[i] = 0;
        obs_comp[i] = 0;
        stone_comp[i] = 0;
        bomb_comp[i] = 0;
        repair_to_home[i] = 0;
        trans_velo[i] = 0;
        clear_velo[i] = 0;
        bomb_velo[i] = 0;
        repair_velo[i] = 0;
        trans_num[i] = 0;
        repair_num[i] = 0;
        bomb_num[i] = 0;
        clear_num[i] = 0;
        obs_table[i] = 0;
        stone_table[i] = 0;
        bomb_table[i] = 0;

        trans_effi[i] = 0;
        bomb_effi[i] = 0;
        clear_effi[i] = 0;
        repair_effi[i] = 0;

        task_plan1.trans_car_team[i].trans_car_over();
        task_plan1.obstacle_team[i].isfinish = 0;
        task_plan1.clear_car_team[i].trans_car_over();
        task_plan1.stone_team[i].isfinish = 0;
        task_plan1.bomb_car_team[i].trans_car_over();
        task_plan1.bomb_team[i].isfinish = 0;
        task_plan1.copter_team[i].copter_over();
    }
    m_timer->stop();
    e_timer->stop();
    h_timer->stop();
    obsSet.clear();
    stoneSet.clear();
    bombSet.clear();



}
void gridmap::Emr_return_task()
{
    m_timer->stop();
    sleep(100);
    e_timer->start(100);
    h_timer->start(250);
    for (int i = 0; i < 20; i++)
    {
        num1[i] = 0;
        numclear[i] = 0;
        numbomb[i] = 0;
    }
    connect(e_timer,&QTimer::timeout,[=]()
    {
        Emergency_repair_return();
        Emergency_copter_return();
        update();

    });
    connect(h_timer,&QTimer::timeout,[=]()
    {
        Emergency_return();
        Emergency_clear_return();
        Emergency_bomb_return();
        update();

    });

}

void gridmap::paintEvent(QPaintEvent *)
{
    gridW = 10*factor;
    gridH = 10*factor;



    //棋盘起点坐标
    startX = gridW;
    startY = gridH;

    QPainter p(this); //创建画家，指定窗口为绘图设备

    p.translate(startX + m_XPtInterval, startY + m_YPtInterval);



    //设置画笔
    QPen pen;
    pen.setWidth(2); //线宽
    p.setPen(pen);  //将画笔交给画家

    //取中间8份画棋盘
    for(int i = 0; i <= 60; i++)
    {
        //横线
        p.drawLine(startX, startY+i*gridH, startX+80*gridW, startY+i*gridH);

        //竖线

    }

    for(int j = 0; j <= 80; j++)
    {
        //横线
        p.drawLine(startX+j*gridW, startY, startX+j*gridW, startY+60*gridH);

        //竖线

    }



    //弹坑,石块，未爆弹
    for(int k = 0; k < obs_num; k++)
    {
        for(int i=0; i<copter_num;i++)
        {

            if((sqrt(((task_plan1.copter_team[i].m_X + 1 - obs_x[k])*(task_plan1.copter_team[i].m_X + 1 - obs_x[k])+(task_plan1.copter_team[i].m_Y + 1 - obs_y[k])*(task_plan1.copter_team[i].m_Y + 1 - obs_y[k])))<sqrt(2))||(sqrt(((task_plan1.copter_team[i].m_X + 1 - obs_x[k])*(task_plan1.copter_team[i].m_X + 1 - obs_x[k])+(task_plan1.copter_team[i].m_Y - obs_y[k] - obs_comp[k])*(task_plan1.copter_team[i].m_Y - obs_y[k] - obs_comp[k])))<sqrt(2)))
            {
                obs_count[k] = 1;
            }
            if((sqrt(((task_plan1.copter_team[i].m_X + 1 - stone_x[k])*(task_plan1.copter_team[i].m_X + 1 - stone_x[k])+(task_plan1.copter_team[i].m_Y + 1 - stone_y[k])*(task_plan1.copter_team[i].m_Y + 1 - stone_y[k])))<sqrt(2))||(sqrt(((task_plan1.copter_team[i].m_X + 1 - stone_x[k])*(task_plan1.copter_team[i].m_X + 1 - stone_x[k])+(task_plan1.copter_team[i].m_Y - stone_y[k] - stone_comp[k])*(task_plan1.copter_team[i].m_Y - stone_y[k] - stone_comp[k])))<sqrt(2)))
            {
                stone_count[k] = 1;
            }
            if((sqrt(((task_plan1.copter_team[i].m_X + 1 - bomb_x[k])*(task_plan1.copter_team[i].m_X + 1 - bomb_x[k])+(task_plan1.copter_team[i].m_Y + 1 - bomb_y[k])*(task_plan1.copter_team[i].m_Y + 1 - bomb_y[k])))<sqrt(2))||(sqrt(((task_plan1.copter_team[i].m_X + 1 - bomb_x[k])*(task_plan1.copter_team[i].m_X + 1 - bomb_x[k])+(task_plan1.copter_team[i].m_Y - bomb_y[k] - bomb_comp[k])*(task_plan1.copter_team[i].m_Y - bomb_y[k] - bomb_comp[k])))<sqrt(2)))
            {
                bomb_count[k] = 1;
            }




            if((obs_x[k]!=0||obs_y[k]!=0)&&(obs_count[k]==1))
            {
                if(obsSet.find(k) == obsSet.end())
                {
                    obsSet.insert(k);
                    obs_table[obstable] = k;
                    obstable++;
                    obstacle_num = obstable;

                }
                for(int i = 0; i < obstacle_num; i++)
                {
                    if(obs_table[i] == k)
                    {
                        if(task_plan1.obstacle_team[i].isfinish != 2)
                        {
                            p.drawPixmap( startX+obs_x[k]*gridW, startY+obs_y[k]*gridH,
                                          obs_comp[k]*gridW, obs_comp[k]*gridH,
                                          obstacle1.pic_obstacle
                                          );
                        }


                    }
                }

            }


            if((stone_x[k]!=0||stone_y[k]!=0)&&(stone_count[k]==1))
            {
                if(stoneSet.find(k) == stoneSet.end())
                {
                    stoneSet.insert(k);
                    stone_table[stonetable] = k;
                    stonetable++;
                    stone_see_num = stonetable;

                    if(trans_crash_flag == 1)
                    {

                        int trans_cmp = 500;
                        int trans_dis[20] = {0};
                        int trans_count = 0;

                        if(!(task_plan1.trans_car_team[trans_crash].m_X==1&&task_plan1.trans_car_team[trans_crash].m_Y==2))
                            task_plan1.trans_car_team[trans_crash].disappear=true;


                        for(int i=0;i<clear_car_num;i++)
                        {
                            if(!task_plan1.clear_car_team[i].disappear)
                            {
                                trans_dis[i] = abs(task_plan1.trans_car_team[trans_crash].m_X-stone_x[stone_table[task_plan1.clear_car_team[i].task_locking[task_plan1.clear_car_team[i].task_locking.size()-1]]])
                                        +abs(task_plan1.trans_car_team[trans_crash].m_Y-stone_y[stone_table[task_plan1.clear_car_team[i].task_locking[task_plan1.clear_car_team[i].task_locking.size()-1]]]);
                                if(trans_dis[i] < trans_cmp)
                                {
                                    trans_cmp = trans_dis[i];
                                    trans_count = i;
                                }

                            }

                        }

                        task_plan1.clear_car_team[trans_count].task_locking.push_back(stone_see_num-1);

                        int trans_cmp2 = 500;
                        int trans_dis2[20] = {0};
                        int trans_count2 = 0;

                        for(int i=0;i<trans_car_num;i++)
                        {
                            if(!task_plan1.trans_car_team[i].disappear)
                            {
                                trans_dis2[i] = abs(obs_x[obs_table[task_plan1.trans_car_team[trans_crash].task_locking[0]]]-obs_x[obs_table[task_plan1.trans_car_team[i].task_locking[task_plan1.trans_car_team[i].task_locking.size()-1]]])
                                        +abs(obs_y[obs_table[task_plan1.trans_car_team[trans_crash].task_locking[0]]]-obs_y[obs_table[task_plan1.trans_car_team[i].task_locking[task_plan1.trans_car_team[i].task_locking.size()-1]]]);
                                if(trans_dis2[i] < trans_cmp2)
                                {
                                    trans_cmp2 = trans_dis2[i];
                                    trans_count2 = i;
                                }

                            }

                        }

                        for(int j=0;j<task_plan1.trans_car_team[trans_crash].task_locking.size();j++)
                        {
                            task_plan1.trans_car_team[trans_count2].task_locking.push_back(task_plan1.trans_car_team[trans_crash].task_locking[j]);


                        }
                        task_plan1.trans_car_team[trans_crash].task_locking.clear();





                        trans_crash_flag = 0;
                    }




                    if(bomb_crash_flag == 1)
                    {
                        int bomb_cmp = 500;
                        int bomb_dis[20] = {0};
                        int bomb_count = 0;
                        if(!(task_plan1.bomb_car_team[bomb_crash].m_X==1&&task_plan1.bomb_car_team[bomb_crash].m_Y==2))
                            task_plan1.bomb_car_team[bomb_crash].disappear=true;

                        for(int i=0;i<clear_car_num;i++)
                        {
                            if(!task_plan1.clear_car_team[i].disappear)
                            {
                                bomb_dis[i] = abs(task_plan1.bomb_car_team[bomb_crash].m_X-stone_x[stone_table[task_plan1.clear_car_team[i].task_locking[task_plan1.clear_car_team[i].task_locking.size()-1]]])
                                        +abs(task_plan1.bomb_car_team[bomb_crash].m_Y-stone_y[stone_table[task_plan1.clear_car_team[i].task_locking[task_plan1.clear_car_team[i].task_locking.size()-1]]]);
                                if(bomb_dis[i] < bomb_cmp)
                                {
                                    bomb_cmp = bomb_dis[i];
                                    bomb_count = i;
                                }

                            }

                        }

                        task_plan1.clear_car_team[bomb_count].task_locking.push_back(stone_see_num-1);

                        int bomb_cmp2 = 500;
                        int bomb_dis2[20] = {0};
                        int bomb_count2 = 0;

                        for(int i=0;i<bomb_car_num;i++)
                        {
                            if(!task_plan1.bomb_car_team[i].disappear)
                            {
                                bomb_dis2[i] = abs(bomb_x[bomb_table[task_plan1.bomb_car_team[bomb_crash].task_locking[0]]]-bomb_x[bomb_table[task_plan1.bomb_car_team[i].task_locking[task_plan1.bomb_car_team[i].task_locking.size()-1]]])
                                        +abs(bomb_y[bomb_table[task_plan1.bomb_car_team[bomb_crash].task_locking[0]]]-bomb_y[bomb_table[task_plan1.bomb_car_team[i].task_locking[task_plan1.bomb_car_team[i].task_locking.size()-1]]]);
                                if(bomb_dis2[i] < bomb_cmp2)
                                {
                                    bomb_cmp2 = bomb_dis2[i];
                                    bomb_count2 = i;
                                }

                            }

                        }

                        for(int j=0;j<task_plan1.bomb_car_team[bomb_crash].task_locking.size();j++)
                        {
                            task_plan1.bomb_car_team[bomb_count2].task_locking.push_back(task_plan1.bomb_car_team[bomb_crash].task_locking[j]);


                        }
                        task_plan1.bomb_car_team[bomb_crash].task_locking.clear();
                        bomb_crash_flag = 0;
                    }


                    if(repair_crash_flag == 1)
                    {
                        int bomb_cmp = 500;
                        int bomb_dis[20] = {0};
                        int bomb_count = 0;
                        if(!(task_plan1.repair_car_team[repair_crash].m_X==1&&task_plan1.repair_car_team[repair_crash].m_Y==2))
                            task_plan1.repair_car_team[repair_crash].disappear=true;

                        for(int i=0;i<clear_car_num;i++)
                        {
                            if(!task_plan1.clear_car_team[i].disappear)
                            {
                                bomb_dis[i] = abs(task_plan1.repair_car_team[repair_crash].m_X-stone_x[stone_table[task_plan1.clear_car_team[i].task_locking[task_plan1.clear_car_team[i].task_locking.size()-1]]])
                                        +abs(task_plan1.repair_car_team[repair_crash].m_Y-stone_y[stone_table[task_plan1.clear_car_team[i].task_locking[task_plan1.clear_car_team[i].task_locking.size()-1]]]);
                                if(bomb_dis[i] < bomb_cmp)
                                {
                                    bomb_cmp = bomb_dis[i];
                                    bomb_count = i;
                                }

                            }

                        }

                        task_plan1.clear_car_team[bomb_count].task_locking.push_back(stone_see_num-1);

                        int bomb_cmp2 = 500;
                        int bomb_dis2[20] = {0};
                        int bomb_count2 = 0;

                        for(int i=0;i<repair_car_num;i++)
                        {
                            if(!task_plan1.repair_car_team[i].disappear)
                            {
                                bomb_dis2[i] = abs(obs_x[obs_table[task_plan1.repair_car_team[repair_crash].task_locking[0]]]-obs_x[obs_table[task_plan1.repair_car_team[i].task_locking[task_plan1.repair_car_team[i].task_locking.size()-1]]])
                                        +abs(obs_y[obs_table[task_plan1.repair_car_team[repair_crash].task_locking[0]]]-obs_y[obs_table[task_plan1.repair_car_team[i].task_locking[task_plan1.repair_car_team[i].task_locking.size()-1]]]);
                                if(bomb_dis2[i] < bomb_cmp2)
                                {
                                    bomb_cmp2 = bomb_dis2[i];
                                    bomb_count2 = i;
                                }

                            }

                        }

                        for(int j=0;j<task_plan1.repair_car_team[repair_crash].task_locking.size();j++)
                        {
                            task_plan1.repair_car_team[bomb_count2].task_locking.push_back(task_plan1.repair_car_team[repair_crash].task_locking[j]);
                            task_plan1.repair_car_team[bomb_count2].task_locking2.push_back(task_plan1.repair_car_team[repair_crash].task_locking[j]);

                        }
                        task_plan1.repair_car_team[repair_crash].task_locking.clear();
                        task_plan1.repair_car_team[repair_crash].task_locking2.clear();

                        repair_crash_flag = 0;
                        repair_to_home[bomb_count2] = 0;
                    }


                    if(clear_crash_flag == 1)
                    {
                        int clear_cmp = 500;
                        int clear_dis[20] = {0};
                        int clear_count = 0;
                        if(!(task_plan1.clear_car_team[clear_crash].m_X==1&&task_plan1.clear_car_team[clear_crash].m_Y==2))
                            task_plan1.clear_car_team[clear_crash].disappear=true;

                        for(int i=0;i<clear_car_num;i++)
                        {
                            if(!task_plan1.clear_car_team[i].disappear)
                            {
                                clear_dis[i] = abs(task_plan1.clear_car_team[clear_crash].m_X-stone_x[stone_table[task_plan1.clear_car_team[i].task_locking[task_plan1.clear_car_team[i].task_locking.size()-1]]])
                                        +abs(task_plan1.clear_car_team[clear_crash].m_Y-stone_y[stone_table[task_plan1.clear_car_team[i].task_locking[task_plan1.clear_car_team[i].task_locking.size()-1]]]);
                                if(clear_dis[i] < clear_cmp)
                                {
                                    clear_cmp = clear_dis[i];
                                    clear_count = i;
                                }

                            }
                        }

                        task_plan1.clear_car_team[clear_count].task_locking.push_back(stone_see_num-1);


                        int clear_cmp2 = 500;
                        int clear_dis2[20] = {0};
                        int clear_count2 = 0;

                        for(int i=0;i<clear_car_num;i++)
                        {
                            if(!task_plan1.clear_car_team[i].disappear)
                            {
                                clear_dis2[i] = abs(stone_x[stone_table[task_plan1.clear_car_team[clear_crash].task_locking[0]]]-stone_x[stone_table[task_plan1.clear_car_team[i].task_locking[task_plan1.clear_car_team[i].task_locking.size()-1]]])
                                        +abs(stone_y[stone_table[task_plan1.clear_car_team[clear_crash].task_locking[0]]]-stone_y[stone_table[task_plan1.clear_car_team[i].task_locking[task_plan1.clear_car_team[i].task_locking.size()-1]]]);
                                if(clear_dis2[i] < clear_cmp2)
                                {
                                    clear_cmp2 = clear_dis2[i];
                                    clear_count2 = i;
                                }

                            }
                        }

                        for(int j=0;j<task_plan1.clear_car_team[clear_crash].task_locking.size();j++)
                        {
                            task_plan1.clear_car_team[clear_count2].task_locking.push_back(task_plan1.clear_car_team[clear_crash].task_locking[j]);


                        }
                        task_plan1.clear_car_team[clear_crash].task_locking.clear();

                        clear_crash_flag = 0;
                    }

                }
                for(int i = 0; i < stone_see_num; i++)
                {
                    if(stone_table[i] == k)
                    {
                        if(stone_comp[k]<2)
                        {
                            if(task_plan1.stone_team[i].isfinish != 2)
                            {
                                p.drawPixmap( startX+stone_x[k]*gridW, startY+stone_y[k]*gridH,
                                              stone_comp[k]*gridW, stone_comp[k]*gridH,
                                              stone1.pic_stone
                                              );
                            }
                        }
                        else
                        {
                            if(task_plan1.stone_team[i].isfinish != 2 && task_plan1.stone_team[i].isfinish2 != 2)
                            {
                                p.drawPixmap( startX+stone_x[k]*gridW, startY+stone_y[k]*gridH,
                                              stone_comp[k]*gridW, stone_comp[k]*gridH,
                                              stone1.pic_stone
                                              );
                            }

                            if(task_plan1.stone_team[i].isfinish == 2 && task_plan1.stone_team[i].isfinish2 != 2)
                            {
                                p.drawPixmap( startX+stone_x[k]*gridW, startY+stone_y[k]*gridH,
                                              1*gridW, 1*gridH,
                                              stone1.pic_tushifang
                                              );
                            }
                        }

                    }
                }

            }

            if((bomb_x[k]!=0||bomb_y[k]!=0)&&(bomb_count[k]==1))
            {
                if(bombSet.find(k) == bombSet.end())
                {
                    bombSet.insert(k);
                    bomb_table[bombtable] = k;
                    bombtable++;
                    bomb_see_num = bombtable;
                }
                for(int i = 0; i < bomb_see_num; i++)
                {
                    if(bomb_table[i] == k)
                    {
                        if(task_plan1.bomb_team[i].isfinish != 2)
                        {
                            p.drawPixmap( startX+bomb_x[k]*gridW, startY+bomb_y[k]*gridH,
                                          bomb_comp[k]*gridW, bomb_comp[k]*gridH,
                                          bomb1.pic_bomb
                                          );
                        }
                    }
                }

            }


        }


    }
    /*画路径*/
    QPen pen1(QColor(255,0,0));
    pen1.setWidth(2); //线宽

    QPen pen2(QColor(0,255,0));
    pen2.setWidth(2); //线宽

    QPen pen3(QColor(0,0,255));
    pen3.setWidth(2); //线宽

    QPen pen4(QColor(255,0,255));
    pen4.setWidth(2); //线宽

    if(trans_start == 1)
        if(show_flag)
        {
            for(int i = 0; i < trans_car_num; i++)
                for(int j = 1; j < task_plan1.trans_car_team[i].count-1; j++)
                {
                    p.setPen(pen1);  //将画笔交给画家
                    //横线
                    p.drawLine(startX+task_plan1.trans_car_team[i].pathpoint[j].x*gridW+0.5*gridW,
                               startY+task_plan1.trans_car_team[i].pathpoint[j].y*gridH+0.5*gridH,
                               startX+task_plan1.trans_car_team[i].pathpoint[j+1].x*gridW+0.5*gridW,
                            startY+task_plan1.trans_car_team[i].pathpoint[j+1].y*gridH+0.5*gridH
                            );
                }
            for(int i = 0; i < bomb_car_num; i++)
                for(int j = 1; j < task_plan1.bomb_car_team[i].count-1; j++)
                {
                    p.setPen(pen2);  //将画笔交给画家
                    //横线
                    p.drawLine(startX+task_plan1.bomb_car_team[i].pathpoint[j].x*gridW+0.5*gridW,
                               startY+task_plan1.bomb_car_team[i].pathpoint[j].y*gridH+0.5*gridH,
                               startX+task_plan1.bomb_car_team[i].pathpoint[j+1].x*gridW+0.5*gridW,
                            startY+task_plan1.bomb_car_team[i].pathpoint[j+1].y*gridH+0.5*gridH
                            );
                }

            for(int i = 0; i < clear_car_num; i++)
                for(int j = 1; j < task_plan1.clear_car_team[i].count-1; j++)
                {
                    p.setPen(pen3);  //将画笔交给画家
                    //横线
                    p.drawLine(startX+task_plan1.clear_car_team[i].pathpoint[j].x*gridW+0.5*gridW,
                               startY+task_plan1.clear_car_team[i].pathpoint[j].y*gridH+0.5*gridH,
                               startX+task_plan1.clear_car_team[i].pathpoint[j+1].x*gridW+0.5*gridW,
                            startY+task_plan1.clear_car_team[i].pathpoint[j+1].y*gridH+0.5*gridH
                            );
                }

            for(int i = 0; i < repair_car_num; i++)
                for(int j = 1; j < task_plan1.repair_car_team[i].count-1; j++)
                {
                    p.setPen(pen4);  //将画笔交给画家
                    //横线
                    p.drawLine(startX+task_plan1.repair_car_team[i].pathpoint[j].x*gridW+0.5*gridW,
                               startY+task_plan1.repair_car_team[i].pathpoint[j].y*gridH+0.5*gridH,
                               startX+task_plan1.repair_car_team[i].pathpoint[j+1].x*gridW+0.5*gridW,
                            startY+task_plan1.repair_car_team[i].pathpoint[j+1].y*gridH+0.5*gridH
                            );
                }
        }

    /*画路径*/
    //                QPen pen1(QColor(255,0,0));
    //                pen1.setWidth(2); //线宽

    //                QPen pen2(QColor(0,255,0));
    //                pen2.setWidth(2); //线宽

    //                QPen pen3(QColor(0,0,255));
    //                pen3.setWidth(2); //线宽

    //                if(trans_start == 1)
    //                    if(show_flag)
    //                    {
    //                        for(int i = 0; i < trans_car_num; i++)
    //                        {
    //                            for(int j = 0; j < task_plan1.trans_car_team[i].count-1; j++)
    //                            {
    //                                p.setPen(pen1);  //将画笔交给画家

    //                                if((task_plan1.trans_car_team[i].pathpoint[j].x < task_plan1.trans_car_team[i].pathpoint[j+1].x)
    //                                        &&(task_plan1.trans_car_team[i].pathpoint[j].y < task_plan1.trans_car_team[i].pathpoint[j+1].y))
    //                                {

    //                                    if(startAngle[i] == 0)
    //                                    {
    //                                        QRectF rect(task_plan1.trans_car_team[i].pathpoint[j].x*gridW+1.5*gridW, task_plan1.trans_car_team[i].pathpoint[j].y*gridH+0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle[i] = 2880;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle[i], spanAngle);
    //                                    }
    //                                    else
    //                                    {
    //                                        if((task_plan1.trans_car_team[i].pathpoint[j+1].x < task_plan1.trans_car_team[i].pathpoint[j+2].x)
    //                                                &&(task_plan1.trans_car_team[i].pathpoint[j+1].y == task_plan1.trans_car_team[i].pathpoint[j+2].y))
    //                                        {
    //                                            QRectF rect(task_plan1.trans_car_team[i].pathpoint[j].x*gridW+0.5*gridW, task_plan1.trans_car_team[i].pathpoint[j].y*gridH+1.5*gridH, 2*gridW, 2*gridH);
    //                                            startAngle[i] = 45 * 16;
    //                                            // 跨越度数
    //                                            int spanAngle = 45 * 16;
    //                                            p.drawArc(rect, startAngle[i], spanAngle);

    //                                            QRectF rect1(task_plan1.trans_car_team[i].pathpoint[j].x*gridW+1.5*gridW, task_plan1.trans_car_team[i].pathpoint[j].y*gridH-1.5*gridH, 4*gridW, 4*gridH);
    //                                            startAngle[i] = 200 * 16;
    //                                            // 跨越度数
    //                                            spanAngle = 70 * 16;
    //                                            p.drawArc(rect1, startAngle[i], spanAngle);
    //                                        }
    //                                        else
    //                                        {
    //                                            QRectF rect(task_plan1.trans_car_team[i].pathpoint[j].x*gridW+0.5*gridW, task_plan1.trans_car_team[i].pathpoint[j].y*gridH+1.5*gridH, 2*gridW, 2*gridH);
    //                                            startAngle[i] = 0;
    //                                            // 跨越度数
    //                                            int spanAngle = 90 * 16;
    //                                            p.drawArc(rect, startAngle[i], spanAngle);
    //                                        }

    //                                    }

    //                                }
    //                                else if((task_plan1.trans_car_team[i].pathpoint[j].x < task_plan1.trans_car_team[i].pathpoint[j+1].x)
    //                                        &&(task_plan1.trans_car_team[i].pathpoint[j].y > task_plan1.trans_car_team[i].pathpoint[j+1].y))
    //                                {

    //                                    if(startAngle1[i] == 1440)
    //                                    {
    //                                        QRectF rect(task_plan1.trans_car_team[i].pathpoint[j].x*gridW+0.5*gridW, task_plan1.trans_car_team[i].pathpoint[j].y*gridH-0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle1[i] = 4320;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle1[i], spanAngle);
    //                                    }
    //                                    else
    //                                    {
    //                                        QRectF rect(task_plan1.trans_car_team[i].pathpoint[j].x*gridW+1.5*gridW, task_plan1.trans_car_team[i].pathpoint[j].y*gridH+0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle1[i] = 1440;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle1[i], spanAngle);
    //                                    }

    //                                }
    //                                else if((task_plan1.trans_car_team[i].pathpoint[j].x > task_plan1.trans_car_team[i].pathpoint[j+1].x)
    //                                        &&(task_plan1.trans_car_team[i].pathpoint[j].y < task_plan1.trans_car_team[i].pathpoint[j+1].y))
    //                                {

    //                                    if(startAngle2[i] == 1440)
    //                                    {
    //                                        QRectF rect(task_plan1.trans_car_team[i].pathpoint[j].x*gridW-0.5*gridW, task_plan1.trans_car_team[i].pathpoint[j].y*gridH+0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle2[i] = 4320;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle2[i], spanAngle);
    //                                    }
    //                                    else
    //                                    {
    //                                        QRectF rect(task_plan1.trans_car_team[i].pathpoint[j].x*gridW+0.5*gridW, task_plan1.trans_car_team[i].pathpoint[j].y*gridH+1.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle2[i] = 1440;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle2[i], spanAngle);
    //                                    }

    //                                }
    //                                else if((task_plan1.trans_car_team[i].pathpoint[j].x > task_plan1.trans_car_team[i].pathpoint[j+1].x)
    //                                        &&(task_plan1.trans_car_team[i].pathpoint[j].y > task_plan1.trans_car_team[i].pathpoint[j+1].y))
    //                                {

    //                                    if(startAngle3[i] == 0)
    //                                    {
    //                                        QRectF rect(task_plan1.trans_car_team[i].pathpoint[j].x*gridW+0.5*gridW, task_plan1.trans_car_team[i].pathpoint[j].y*gridH-0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle3[i] = 2880;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle3[i], spanAngle);
    //                                    }
    //                                    else
    //                                    {
    //                                        QRectF rect(task_plan1.trans_car_team[i].pathpoint[j].x*gridW-0.5*gridW, task_plan1.trans_car_team[i].pathpoint[j].y*gridH+0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle3[i] = 0;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle3[i], spanAngle);
    //                                    }

    //                                }
    //                                else
    //                                {
    //                                    p.drawLine(startX+task_plan1.trans_car_team[i].pathpoint[j].x*gridW+0.5*gridW,
    //                                               startY+task_plan1.trans_car_team[i].pathpoint[j].y*gridH+0.5*gridH,
    //                                               startX+task_plan1.trans_car_team[i].pathpoint[j+1].x*gridW+0.5*gridW,
    //                                            startY+task_plan1.trans_car_team[i].pathpoint[j+1].y*gridH+0.5*gridH
    //                                            );
    //                                }

    //                            }
    //                            startAngle[i] = 0;
    //                            startAngle1[i] = 1440;
    //                            startAngle2[i] = 1440;
    //                            startAngle3[i] = 0;
    //                        }

    //                        for(int i = 0; i < bomb_car_num; i++)
    //                        {
    //                            for(int j = 0; j < task_plan1.bomb_car_team[i].count-1; j++)
    //                            {
    //                                p.setPen(pen2);  //将画笔交给画家
    //                                //横线
    //                                if((task_plan1.bomb_car_team[i].pathpoint[j].x < task_plan1.bomb_car_team[i].pathpoint[j+1].x)
    //                                        &&(task_plan1.bomb_car_team[i].pathpoint[j].y < task_plan1.bomb_car_team[i].pathpoint[j+1].y))
    //                                {

    //                                    if(startAngle[i] == 0)
    //                                    {
    //                                        QRectF rect(task_plan1.bomb_car_team[i].pathpoint[j].x*gridW+1.5*gridW, task_plan1.bomb_car_team[i].pathpoint[j].y*gridH+0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle[i] = 2880;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle[i], spanAngle);
    //                                    }
    //                                    else
    //                                    {
    //                                        QRectF rect(task_plan1.bomb_car_team[i].pathpoint[j].x*gridW+0.5*gridW, task_plan1.bomb_car_team[i].pathpoint[j].y*gridH+1.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle[i] = 0;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle[i], spanAngle);
    //                                    }

    //                                }
    //                                else if((task_plan1.bomb_car_team[i].pathpoint[j].x < task_plan1.bomb_car_team[i].pathpoint[j+1].x)
    //                                        &&(task_plan1.bomb_car_team[i].pathpoint[j].y > task_plan1.bomb_car_team[i].pathpoint[j+1].y))
    //                                {

    //                                    if(startAngle1[i] == 1440)
    //                                    {
    //                                        QRectF rect(task_plan1.bomb_car_team[i].pathpoint[j].x*gridW+0.5*gridW, task_plan1.bomb_car_team[i].pathpoint[j].y*gridH-0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle1[i] = 4320;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle1[i], spanAngle);
    //                                    }
    //                                    else
    //                                    {
    //                                        QRectF rect(task_plan1.bomb_car_team[i].pathpoint[j].x*gridW+1.5*gridW, task_plan1.bomb_car_team[i].pathpoint[j].y*gridH+0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle1[i] = 1440;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle1[i], spanAngle);
    //                                    }

    //                                }
    //                                else if((task_plan1.bomb_car_team[i].pathpoint[j].x > task_plan1.bomb_car_team[i].pathpoint[j+1].x)
    //                                        &&(task_plan1.bomb_car_team[i].pathpoint[j].y < task_plan1.bomb_car_team[i].pathpoint[j+1].y))
    //                                {

    //                                    if(startAngle2[i] == 1440)
    //                                    {
    //                                        QRectF rect(task_plan1.bomb_car_team[i].pathpoint[j].x*gridW-0.5*gridW, task_plan1.bomb_car_team[i].pathpoint[j].y*gridH+0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle2[i] = 4320;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle2[i], spanAngle);
    //                                    }
    //                                    else
    //                                    {
    //                                        QRectF rect(task_plan1.bomb_car_team[i].pathpoint[j].x*gridW+0.5*gridW, task_plan1.bomb_car_team[i].pathpoint[j].y*gridH+1.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle2[i] = 1440;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle2[i], spanAngle);
    //                                    }

    //                                }
    //                                else if((task_plan1.bomb_car_team[i].pathpoint[j].x > task_plan1.bomb_car_team[i].pathpoint[j+1].x)
    //                                        &&(task_plan1.bomb_car_team[i].pathpoint[j].y > task_plan1.bomb_car_team[i].pathpoint[j+1].y))
    //                                {

    //                                    if(startAngle3[i] == 0)
    //                                    {
    //                                        QRectF rect(task_plan1.bomb_car_team[i].pathpoint[j].x*gridW+0.5*gridW, task_plan1.bomb_car_team[i].pathpoint[j].y*gridH-0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle3[i] = 2880;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle3[i], spanAngle);
    //                                    }
    //                                    else
    //                                    {
    //                                        QRectF rect(task_plan1.bomb_car_team[i].pathpoint[j].x*gridW-0.5*gridW, task_plan1.bomb_car_team[i].pathpoint[j].y*gridH+0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle3[i] = 0;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle3[i], spanAngle);
    //                                    }

    //                                }
    //                                else
    //                                {
    //                                    p.drawLine(startX+task_plan1.bomb_car_team[i].pathpoint[j].x*gridW+0.5*gridW,
    //                                               startY+task_plan1.bomb_car_team[i].pathpoint[j].y*gridH+0.5*gridH,
    //                                               startX+task_plan1.bomb_car_team[i].pathpoint[j+1].x*gridW+0.5*gridW,
    //                                            startY+task_plan1.bomb_car_team[i].pathpoint[j+1].y*gridH+0.5*gridH
    //                                            );
    //                                }

    //                            }
    //                            startAngle[i] = 0;
    //                            startAngle1[i] = 1440;
    //                            startAngle2[i] = 1440;
    //                            startAngle3[i] = 0;
    //                        }


    //                        for(int i = 0; i < clear_car_num; i++)
    //                        {
    //                            for(int j = 0; j < task_plan1.clear_car_team[i].count-1; j++)
    //                            {
    //                                p.setPen(pen3);  //将画笔交给画家
    //                                //横线
    //                                if((task_plan1.clear_car_team[i].pathpoint[j].x < task_plan1.clear_car_team[i].pathpoint[j+1].x)
    //                                        &&(task_plan1.clear_car_team[i].pathpoint[j].y < task_plan1.clear_car_team[i].pathpoint[j+1].y))
    //                                {

    //                                    if(startAngle[i] == 0)
    //                                    {
    //                                        QRectF rect(task_plan1.clear_car_team[i].pathpoint[j].x*gridW+1.5*gridW, task_plan1.clear_car_team[i].pathpoint[j].y*gridH+0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle[i] = 2880;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle[i], spanAngle);
    //                                    }
    //                                    else
    //                                    {
    //                                        QRectF rect(task_plan1.clear_car_team[i].pathpoint[j].x*gridW+0.5*gridW, task_plan1.clear_car_team[i].pathpoint[j].y*gridH+1.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle[i] = 0;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle[i], spanAngle);
    //                                    }

    //                                }
    //                                else if((task_plan1.clear_car_team[i].pathpoint[j].x < task_plan1.clear_car_team[i].pathpoint[j+1].x)
    //                                        &&(task_plan1.clear_car_team[i].pathpoint[j].y > task_plan1.clear_car_team[i].pathpoint[j+1].y))
    //                                {

    //                                    if(startAngle1[i] == 1440)
    //                                    {
    //                                        QRectF rect(task_plan1.clear_car_team[i].pathpoint[j].x*gridW+0.5*gridW, task_plan1.clear_car_team[i].pathpoint[j].y*gridH-0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle1[i] = 4320;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle1[i], spanAngle);
    //                                    }
    //                                    else
    //                                    {
    //                                        QRectF rect(task_plan1.clear_car_team[i].pathpoint[j].x*gridW+1.5*gridW, task_plan1.clear_car_team[i].pathpoint[j].y*gridH+0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle1[i] = 1440;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle1[i], spanAngle);
    //                                    }

    //                                }
    //                                else if((task_plan1.clear_car_team[i].pathpoint[j].x > task_plan1.clear_car_team[i].pathpoint[j+1].x)
    //                                        &&(task_plan1.clear_car_team[i].pathpoint[j].y < task_plan1.clear_car_team[i].pathpoint[j+1].y))
    //                                {

    //                                    if(startAngle2[i] == 1440)
    //                                    {
    //                                        QRectF rect(task_plan1.clear_car_team[i].pathpoint[j].x*gridW-0.5*gridW, task_plan1.clear_car_team[i].pathpoint[j].y*gridH+0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle2[i] = 4320;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle2[i], spanAngle);
    //                                    }
    //                                    else
    //                                    {
    //                                        QRectF rect(task_plan1.clear_car_team[i].pathpoint[j].x*gridW+0.5*gridW, task_plan1.clear_car_team[i].pathpoint[j].y*gridH+1.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle2[i] = 1440;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle2[i], spanAngle);
    //                                    }

    //                                }
    //                                else if((task_plan1.clear_car_team[i].pathpoint[j].x > task_plan1.clear_car_team[i].pathpoint[j+1].x)
    //                                        &&(task_plan1.clear_car_team[i].pathpoint[j].y > task_plan1.clear_car_team[i].pathpoint[j+1].y))
    //                                {

    //                                    if(startAngle3[i] == 0)
    //                                    {
    //                                        QRectF rect(task_plan1.clear_car_team[i].pathpoint[j].x*gridW+0.5*gridW, task_plan1.clear_car_team[i].pathpoint[j].y*gridH-0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle3[i] = 2880;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle3[i], spanAngle);
    //                                    }
    //                                    else
    //                                    {
    //                                        QRectF rect(task_plan1.clear_car_team[i].pathpoint[j].x*gridW-0.5*gridW, task_plan1.clear_car_team[i].pathpoint[j].y*gridH+0.5*gridH, 2*gridW, 2*gridH);
    //                                        startAngle3[i] = 0;
    //                                        // 跨越度数
    //                                        int spanAngle = 90 * 16;
    //                                        p.drawArc(rect, startAngle3[i], spanAngle);
    //                                    }

    //                                }
    //                                else
    //                                {
    //                                    p.drawLine(startX+task_plan1.clear_car_team[i].pathpoint[j].x*gridW+0.5*gridW,
    //                                               startY+task_plan1.clear_car_team[i].pathpoint[j].y*gridH+0.5*gridH,
    //                                               startX+task_plan1.clear_car_team[i].pathpoint[j+1].x*gridW+0.5*gridW,
    //                                            startY+task_plan1.clear_car_team[i].pathpoint[j+1].y*gridH+0.5*gridH
    //                                            );
    //                                }

    //                            }
    //                            startAngle[i] = 0;
    //                            startAngle1[i] = 1440;
    //                            startAngle2[i] = 1440;
    //                            startAngle3[i] = 0;
    //                        }

    //                    }


    for(int i = 0; i < repair_car_num; i++)
    {
        if(!task_plan1.repair_car_team[i].disappear)
        {
            p.drawPixmap( startX+task_plan1.repair_car_team[i].m_X*gridW, startY+task_plan1.repair_car_team[i].m_Y*gridH,
                          gridW, gridH,
                          task_plan1.repair_car_team[i].pic_repair_car
                          );
        }

    }



    for(int i = 0; i < trans_car_num; i++)
    {
        if(!task_plan1.trans_car_team[i].disappear)
        {
            p.drawPixmap( startX+task_plan1.trans_car_team[i].m_X*gridW, startY+task_plan1.trans_car_team[i].m_Y*gridH,
                          gridW, gridH,
                          task_plan1.trans_car_team[i].pic_tans_car
                          );
        }

    }

    for(int i = 0; i < clear_car_num; i++)
    {
        if(!task_plan1.clear_car_team[i].disappear)
        {
            p.drawPixmap( startX+task_plan1.clear_car_team[i].m_X*gridW, startY+task_plan1.clear_car_team[i].m_Y*gridH,
                          gridW, gridH,
                          task_plan1.clear_car_team[i].pic_clear_car
                          );
        }

    }

    for(int i = 0; i < bomb_car_num; i++)
    {
        if(!task_plan1.bomb_car_team[i].disappear)
        {
            p.drawPixmap( startX+task_plan1.bomb_car_team[i].m_X*gridW, startY+task_plan1.bomb_car_team[i].m_Y*gridH,
                          gridW, gridH,
                          task_plan1.bomb_car_team[i].pic_bomb_car
                          );
        }

    }

    //画飞机
    for(int i=0; i < copter_num;i++)
        p.drawPixmap( startX+task_plan1.copter_team[i].m_X*gridW, startY+task_plan1.copter_team[i].m_Y*gridH,
                      gridW, gridH,
                      task_plan1.copter_team[i].pic_transcar
                      );


}


bool change_flag=false;
bool wait_flag=false;
bool change_routine=false;
void gridmap::updataposition()
{
    copter_check1=0;
    copter_check2=0;
    for(int i = 0; i < copter_num; i++)
    {
        if(task_plan1.copter_team[i].reback_step1==1)
            copter_check1++;
        if(task_plan1.copter_team[i].reback_step2==1)
            copter_check2++;

    } //确保在一条直线上再回程
    /*紧急返航后再开始回到原来的点*/
    if(copter_flag[0] ==1 )
    {   if(task_plan1.copter_team[0].m_Y < copter_last_m_Y[0])
        {
            task_plan1.copter_team[0].m_Y = task_plan1.copter_team[0].m_Y + 1;
        }
        if(task_plan1.copter_team[0].m_X < copter_last_m_X[0])
        {
            task_plan1.copter_team[0].m_X = task_plan1.copter_team[0].m_X + 1;
        }

        if(task_plan1.copter_team[0].m_X == copter_last_m_X[0]

                &&task_plan1.copter_team[0].m_Y == copter_last_m_Y[0]   )
        {
            copter_flag[0] =0 ;
        }
    }

    for(int i = 1; i < copter_num; i++)
    {
        if(copter_flag[i] == 1)
        {
            if(abs(task_plan1.copter_team[i].m_X-task_plan1.copter_team[i-1].m_X)+abs(task_plan1.copter_team[i].m_Y-task_plan1.copter_team[i-1].m_Y)>2)
            {
                if(task_plan1.copter_team[i].m_Y < copter_last_m_Y[i])
                {
                    task_plan1.copter_team[i].m_Y = task_plan1.copter_team[i].m_Y + 1;
                }
                if(task_plan1.copter_team[i].m_X < copter_last_m_X[i])
                {
                    task_plan1.copter_team[i].m_X = task_plan1.copter_team[i].m_X + 1;
                }

            }


            if(task_plan1.copter_team[i].m_X == copter_last_m_X[i]

                    &&task_plan1.copter_team[i].m_Y == copter_last_m_Y[i]   )
            {
                copter_flag[i] =0 ;
            }

        }


    }

    /*正常开始*/
    if(copter_flag[0] ==0 )
        task_plan1.copter_team[0].setPosition();
    for(int i = 1; i < copter_num; i++)
    {   if(copter_flag[i] ==0 )
        {
            if(abs(task_plan1.copter_team[i].m_X-task_plan1.copter_team[i-1].m_X)+abs(task_plan1.copter_team[i].m_Y-task_plan1.copter_team[i-1].m_Y)>2)
                task_plan1.copter_team[i].setPosition();
            if(task_plan1.copter_team[copter_num-1].rebackflag==1)
                task_plan1.copter_team[i].setPosition();
        }
    }




    if( task_plan1.copter_team[copter_num-1].rebackflag==1 && copter_repeat == 0)
//        ( task_plan1.copter_team[0].m_Y==6 && task_plan1.copter_team[0].m_X==6 && copter_repeat == 0)
    {
        for(int i = 0; i < trans_car_num; i++)
        {
            for(int j = 0; j < obstacle_num; j++)
            {
                maze.clear();
                for(int m=0; m<60; m++)
                {
                    std::vector<int> rowMaze;
                    rowMaze.clear();
                    for(int n=0; n<80; n++)
                    {
                        if(((m>=obs_y[obs_table[j]])&&(m<(obs_y[obs_table[j]]+obs_comp[obs_table[j]]))) && ((n>=obs_x[obs_table[j]])&&(n<(obs_x[obs_table[j]]+obs_comp[obs_table[j]]))))
                        {
                            m_obs = true;
                        }

                        for(int k = 0; k < stone_see_num; k++)
                        {
                            if(((m>=stone_y[stone_table[k]])&&(m<(stone_y[stone_table[k]]+stone_comp[stone_table[k]]))) && ((n>=stone_x[stone_table[k]])&&(n<(stone_x[stone_table[k]]+stone_comp[stone_table[k]]))))
                            {
                                m_obs = true;
                            }
                        }
                        for(int l = 0; l < bomb_see_num; l++)
                        {
                            if(((m>=bomb_y[bomb_table[l]])&&(m<(bomb_y[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && ((n>=bomb_x[bomb_table[l]])&&(n<(bomb_x[bomb_table[l]]+bomb_comp[bomb_table[l]]))))
                            {
                                m_obs = true;
                            }
                        }

                        if((m==obs_y[obs_table[j]])&&(n==obs_x[obs_table[j]]))
                        {
                            m_obs = false;
                        }

                        rowMaze.push_back((int)m_obs);
                        std::cout<<rowMaze.back();
                        m_obs = false;
                    }
                    std::cout<<std::endl;
                    maze.push_back(rowMaze);

                }
                task_plan1.trans_car_team[i].astar.InitAstar(maze);
                task_plan1.trans_car_team[i].findpath_astar(2, 1, obs_y[obs_table[j]], obs_x[obs_table[j]]);
                task_plan1.trans_car_team[i].task_time.push_back(50*obs_comp[obs_table[j]]/trans_effi[i]+(task_plan1.trans_car_team[i].count - 1)*100/trans_velo[i]);
            }
        }


        if(trans_car_num != 0 && obstacle_num != 0)
        {
            int t_trans_task = 0;
            int comp_trans_task = 0;
            for(int i = 0; i < trans_car_num; i++)
            {
                for(int j = 0; j < task_plan1.trans_car_team[i].task_time.size(); j++)
                {
                    t_trans_task += task_plan1.trans_car_team[i].task_time[j];
                }


            }

            for(int i = 0; i < obstacle_num; i++)
            {
                comp_trans_task += 50*obs_comp[i] ;

            }
            t_trans_task_average = t_trans_task/(trans_car_num*trans_car_num);

            time_trans_limit_up = 1.05 * t_trans_task_average;
            time_trans_limit_down = 0.95 * t_trans_task_average;


            task_plan1.trans_car_plan();
        }









        for(int i = 0; i < clear_car_num; i++)
        {
            for(int j = 0; j < stone_see_num; j++)
            {
                maze.clear();
                for(int m=0; m<60; m++)
                {
                    std::vector<int> rowMaze;
                    rowMaze.clear();
                    for(int n=0; n<80; n++)
                    {
                        if(((m>=stone_y[stone_table[j]])&&(m<(stone_y[stone_table[j]]+stone_comp[stone_table[j]]))) && ((n>=stone_x[stone_table[j]])&&(n<(stone_x[stone_table[j]]+stone_comp[stone_table[j]]))))
                        {
                            m_obs = true;
                        }

                        for(int k = 0; k < obstacle_num; k++)
                        {
                            if(((m>=obs_y[obs_table[k]])&&(m<(obs_y[obs_table[k]]+obs_comp[obs_table[k]]))) && ((n>=obs_x[obs_table[k]])&&(n<(obs_x[obs_table[k]]+obs_comp[obs_table[k]]))))
                            {
                                m_obs = true;
                            }
                        }
                        for(int l = 0; l < bomb_see_num; l++)
                        {
                            if(((m>=bomb_y[bomb_table[l]])&&(m<(bomb_y[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && ((n>=bomb_x[bomb_table[l]])&&(n<(bomb_x[bomb_table[l]]+bomb_comp[bomb_table[l]]))))
                            {
                                m_obs = true;
                            }
                        }
                        if((m==stone_y[stone_table[j]])&&(n==stone_x[stone_table[j]]))
                        {
                            m_obs = false;
                        }
                        rowMaze.push_back((int)m_obs);
                        std::cout<<rowMaze.back();
                        m_obs = false;
                    }
                    std::cout<<std::endl;
                    maze.push_back(rowMaze);

                }
                task_plan1.clear_car_team[i].astar.InitAstar(maze);
                task_plan1.clear_car_team[i].findpath_astar(2, 1, stone_y[stone_table[j]], stone_x[stone_table[j]]);
                task_plan1.clear_car_team[i].task_time.push_back(50*stone_comp[stone_table[j]]/clear_effi[i]+(task_plan1.clear_car_team[i].count - 1)*100/clear_velo[i]);
            }
        }

        if(clear_car_num != 0 && stone_see_num != 0)
        {
            int t_clear_task = 0;
            int comp_clear_task = 0;
            for(int i = 0; i < clear_car_num; i++)
            {
                for(int j = 0; j < task_plan1.clear_car_team[i].task_time.size(); j++)
                {
                    t_clear_task += task_plan1.clear_car_team[i].task_time[j];
                }


            }

            for(int i = 0; i < stone_see_num; i++)
            {
                comp_clear_task += 50*stone_comp[i];

            }
            t_clear_task_average = t_clear_task/(clear_car_num*clear_car_num) ;

            time_clear_limit_up = 1.05 * t_clear_task_average;
            time_clear_limit_down = 0.95 * t_clear_task_average;


            task_plan1.clear_car_plan();
        }











        for(int i = 0; i < bomb_car_num; i++)
        {
            for(int j = 0; j < bomb_see_num; j++)
            {
                maze.clear();
                for(int m=0; m<60; m++)
                {
                    std::vector<int> rowMaze;
                    rowMaze.clear();
                    for(int n=0; n<80; n++)
                    {
                        if(((m>=bomb_y[bomb_table[j]])&&(m<(bomb_y[bomb_table[j]]+bomb_comp[bomb_table[j]]))) && ((n>=bomb_x[bomb_table[j]])&&(n<(bomb_x[bomb_table[j]]+bomb_comp[bomb_table[j]]))))
                        {
                            m_obs = true;
                        }

                        for(int k = 0; k < obstacle_num; k++)
                        {
                            if(((m>=obs_y[obs_table[k]])&&(m<(obs_y[obs_table[k]]+obs_comp[obs_table[k]]))) && ((n>=obs_x[obs_table[k]])&&(n<(obs_x[obs_table[k]]+obs_comp[obs_table[k]]))))
                            {
                                m_obs = true;
                            }
                        }
                        for(int l = 0; l < stone_see_num; l++)
                        {
                            if(((m>=stone_y[stone_table[l]])&&(m<(stone_y[stone_table[l]]+stone_comp[stone_table[l]]))) && ((n>=stone_x[stone_table[l]])&&(n<(stone_x[stone_table[l]]+stone_comp[stone_table[l]]))))
                            {
                                m_obs = true;
                            }
                        }
                        if((m==bomb_y[bomb_table[j]])&&(n==bomb_x[bomb_table[j]]))
                        {
                            m_obs = false;
                        }
                        rowMaze.push_back((int)m_obs);
                        std::cout<<rowMaze.back();
                        m_obs = false;
                    }
                    std::cout<<std::endl;
                    maze.push_back(rowMaze);

                }
                task_plan1.bomb_car_team[i].astar.InitAstar(maze);
                task_plan1.bomb_car_team[i].findpath_astar(2, 1, bomb_y[bomb_table[j]], bomb_x[bomb_table[j]]);
                task_plan1.bomb_car_team[i].task_time.push_back(50*bomb_comp[obs_table[j]]/bomb_effi[i]+(task_plan1.bomb_car_team[i].count - 1)*100/bomb_velo[i]);
            }
        }

        if(bomb_car_num != 0 && bomb_see_num != 0)
        {
            int t_bomb_task = 0;
            int comp_bomb_task = 0;
            for(int i = 0; i < bomb_car_num; i++)
            {
                for(int j = 0; j < task_plan1.bomb_car_team[i].task_time.size(); j++)
                {
                    t_bomb_task += task_plan1.bomb_car_team[i].task_time[j];
                }


            }

            for(int i = 0; i < bomb_see_num; i++)
            {
                comp_bomb_task += 50*bomb_comp[i];

            }
            t_bomb_task_average = t_bomb_task/(bomb_car_num*bomb_car_num);

            time_bomb_limit_up = 1.05 * t_bomb_task_average;
            time_bomb_limit_down = 0.95 * t_bomb_task_average;


            task_plan1.bomb_car_plan();
        }



        for(int i = 0; i < repair_car_num; i++)
        {
            for(int j = 0; j < obstacle_num; j++)
            {
                maze.clear();
                for(int m=0; m<60; m++)
                {
                    std::vector<int> rowMaze;
                    rowMaze.clear();
                    for(int n=0; n<80; n++)
                    {
                        if(((m>=obs_y[obs_table[j]])&&(m<(obs_y[obs_table[j]]+obs_comp[obs_table[j]]))) && ((n>=obs_x[obs_table[j]])&&(n<(obs_x[obs_table[j]]+obs_comp[obs_table[j]]))))
                        {
                            m_obs = true;
                        }

                        for(int k = 0; k < stone_see_num; k++)
                        {
                            if(((m>=stone_y[stone_table[k]])&&(m<(stone_y[stone_table[k]]+stone_comp[stone_table[k]]))) && ((n>=stone_x[stone_table[k]])&&(n<(stone_x[stone_table[k]]+stone_comp[stone_table[k]]))))
                            {
                                m_obs = true;
                            }
                        }
                        for(int l = 0; l < bomb_see_num; l++)
                        {
                            if(((m>=bomb_y[bomb_table[l]])&&(m<(bomb_y[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && ((n>=bomb_x[bomb_table[l]])&&(n<(bomb_x[bomb_table[l]]+bomb_comp[bomb_table[l]]))))
                            {
                                m_obs = true;
                            }
                        }

                        if((m==obs_y[obs_table[j]])&&(n==obs_x[obs_table[j]]))
                        {
                            m_obs = false;
                        }

                        rowMaze.push_back((int)m_obs);
                        std::cout<<rowMaze.back();
                        m_obs = false;
                    }
                    std::cout<<std::endl;
                    maze.push_back(rowMaze);

                }
                task_plan1.repair_car_team[i].astar.InitAstar(maze);
                task_plan1.repair_car_team[i].findpath_astar(2, 1, obs_y[obs_table[j]], obs_x[obs_table[j]]);
                task_plan1.repair_car_team[i].task_time.push_back((task_plan1.repair_car_team[i].count - 1));
            }
        }


        if(repair_car_num != 0 && obstacle_num != 0)
        {
            int t_trans_task = 0;
            int comp_trans_task = 0;
            for(int i = 0; i <repair_car_num ; i++)
            {
                for(int j = 0; j < task_plan1.repair_car_team[i].task_time.size(); j++)
                {
                    t_trans_task += task_plan1.repair_car_team[i].task_time[j];
                }


            }

            for(int i = 0; i < obstacle_num; i++)
            {
                comp_trans_task += 10*obs_comp[i] ;

            }
            t_repair_task_average = t_trans_task/(repair_car_num*repair_car_num);

            time_repair_limit_up = 1.05 * t_repair_task_average;
            time_repair_limit_down = 0.95 * t_repair_task_average;


            task_plan1.repair_car_plan();
        }






        for(int i = 0; i < repair_car_num; i++)
        {
            for(int j = 0; j < stone_see_num; j++)
            {
                if(stone_comp[stone_table[j]] >= 2)
                {
                    repair_need++;
                    maze.clear();
                    for(int m=0; m<60; m++)
                    {
                        std::vector<int> rowMaze;
                        rowMaze.clear();
                        for(int n=0; n<80; n++)
                        {
                            if(((m>=obs_y[obs_table[j]])&&(m<(obs_y[obs_table[j]]+obs_comp[obs_table[j]]))) && ((n>=obs_x[obs_table[j]])&&(n<(obs_x[obs_table[j]]+obs_comp[obs_table[j]]))))
                            {
                                m_obs = true;
                            }

                            for(int k = 0; k < stone_see_num; k++)
                            {
                                if(((m>=stone_y[stone_table[k]])&&(m<(stone_y[stone_table[k]]+stone_comp[stone_table[k]]))) && ((n>=stone_x[stone_table[k]])&&(n<(stone_x[stone_table[k]]+stone_comp[stone_table[k]]))))
                                {
                                    m_obs = true;
                                }
                            }
                            for(int l = 0; l < bomb_see_num; l++)
                            {
                                if(((m>=bomb_y[bomb_table[l]])&&(m<(bomb_y[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && ((n>=bomb_x[bomb_table[l]])&&(n<(bomb_x[bomb_table[l]]+bomb_comp[bomb_table[l]]))))
                                {
                                    m_obs = true;
                                }
                            }

                            if((m==stone_y[stone_table[j]])&&(n==stone_x[stone_table[j]]))
                            {
                                m_obs = false;
                            }

                            rowMaze.push_back((int)m_obs);
                            std::cout<<rowMaze.back();
                            m_obs = false;
                        }
                        std::cout<<std::endl;
                        maze.push_back(rowMaze);

                    }
                    task_plan1.repair_car_team[i].astar.InitAstar(maze);
                    task_plan1.repair_car_team[i].findpath_astar(2, 1, stone_y[stone_table[j]], stone_x[stone_table[j]]);
                    task_plan1.repair_car_team[i].task_time2.push_back((task_plan1.repair_car_team[i].count - 1));
                }
            }
        }

        if(repair_car_num != 0 && repair_need != 0)
        {
            int t_trans_task = 0;
            int comp_trans_task = 0;
            for(int a = 0; a < repair_car_num; a++)
            {
                for(int b = 0; b < task_plan1.repair_car_team[a].task_time2.size(); b++)
                {
                    t_trans_task += task_plan1.repair_car_team[a].task_time2[b];
                }


            }

            for(int a = 0; a < stone_see_num; a++)
            {
                if(stone_comp[stone_table[a]] >= 2)
                {
                    comp_trans_task += 5*stone_comp[stone_table[a]];
                }


            }
            t_repair_task_average2 = t_trans_task/(repair_car_num*repair_car_num) ;

            time_repair_limit_up2 = 1.05 * t_repair_task_average2;
            time_repair_limit_down2 = 0.95 * t_repair_task_average2;


            task_plan1.repair_car_plan2();

            repair_to_clear_start = 1;
        }




        copter_repeat = 1;
        trans_start = 1;
    }


    if(trans_start == 1)
    {

        for(int i = 0; i < repair_car_num; i++)
        {
            repair_time[i]++;
            if(repair_time[i] == (11-repair_velo[i]/10))
            {
                repair_time[i] = 0;
                wait_flag=false;
                change_routine=false;
                if(repair_to_home[i] == 1)
                {
                    for(int j = 0;j < task_plan1.repair_car_team[i].task_locking2.size(); j++)
                    {
                        if(task_plan1.stone_team[task_plan1.repair_car_team[i].task_locking2[j]].isfinish2 == 2)
                        {

                            if(j == (task_plan1.repair_car_team[i].task_locking2.size() - 1))
                            {
                                /*前方有炸弹车*/
                                for(int r = 0; r < bomb_car_num; r++)
                                { int a=task_plan1.bomb_car_team[r].m_Y;
                                    int b=task_plan1.bomb_car_team[r].m_X;
                                    if(numrepairback2[i]<task_plan1.repair_car_team[i].count
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback2[i]+2].y==a
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback2[i]+2].x==b
                                            &&!task_plan1.bomb_car_team[r].disappear)
                                    {
                                        change_routine=true;
                                        break;
                                    }
                                }
                                /*前方有运输车*/
                                for(int r = 0; r < trans_car_num; r++)
                                    if(numrepairback2[i]<task_plan1.repair_car_team[i].count
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback2[i]+2].y==(task_plan1.trans_car_team[r].m_Y)
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback2[i]+2].x==task_plan1.trans_car_team[r].m_X
                                            &&!task_plan1.trans_car_team[r].disappear)
                                    {
                                        change_routine=true;
                                        break;
                                    }
                                /*防止清理车路线重合*/
                                for(int r = 0; r < clear_car_num; r++)
                                    if(numrepairback2[i]<task_plan1.repair_car_team[i].count
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback2[i]+2].y==(task_plan1.clear_car_team[r].m_Y)
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback2[i]+2].x==task_plan1.clear_car_team[r].m_X
                                            &&!task_plan1.clear_car_team[r].disappear)
                                    {
                                        change_routine=true;
                                        break;
                                    }

                                for(int r = 0; r < repair_car_num; r++)
                                    if(numrepairback2[i]<task_plan1.repair_car_team[i].count
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback2[i]+2].y==(task_plan1.repair_car_team[r].m_Y)
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback2[i]+2].x==task_plan1.repair_car_team[r].m_X
                                            &&!task_plan1.repair_car_team[r].disappear)
                                    {
                                        change_routine=true;
                                        break;
                                    }

                                if(task_plan1.repair_car_team[i].pathpoint[numrepairback2[i]+2].y==2
                                        &&task_plan1.repair_car_team[i].pathpoint[numrepairback2[i]+2].x==1)
                                    change_routine=false;
                                numrepairback2[i]++;

                                maze.clear();
                                for(int m=0; m<60; m++)
                                {
                                    std::vector<int> rowMaze;
                                    rowMaze.clear();
                                    for(int n=0; n<80; n++)
                                    {
                                        for(int k = 0; k < stone_see_num; k++)
                                        {
                                            if(((m>=stone_y[stone_table[k]])&&(m<(stone_y[stone_table[k]]+stone_comp[stone_table[k]]))) && ((n>=stone_x[stone_table[k]])&&(n<(stone_x[stone_table[k]]+stone_comp[stone_table[k]]))) && (task_plan1.stone_team[k].isfinish != 2))
                                            {
                                                m_obs = true;
                                            }
                                        }

                                        for(int p = 0; p < obstacle_num; p++)
                                        {
                                            if(((m>=obs_y[obs_table[p]])&&(m<(obs_y[obs_table[p]]+obs_comp[obs_table[p]]))) && ((n>=obs_x[obs_table[p]])&&(n<(obs_x[obs_table[p]]+obs_comp[obs_table[p]]))) && (task_plan1.obstacle_team[p].isfinish != 2))
                                            {
                                                m_obs = true;
                                            }
                                        }
                                        for(int l = 0; l < bomb_see_num; l++)
                                        {
                                            if(((m>=bomb_y[bomb_table[l]])&&(m<(bomb_y[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && ((n>=bomb_x[bomb_table[l]])&&(n<(bomb_x[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && (task_plan1.bomb_team[l].isfinish != 2))
                                            {
                                                m_obs = true;
                                            }
                                        }

                                        if((m==stone_y[stone_table[task_plan1.repair_car_team[i].task_locking2[j]]])&&(n==stone_x[stone_table[task_plan1.repair_car_team[i].task_locking2[j]]]))
                                        {
                                            m_obs = false;
                                        }
                                        if (change_routine)
                                            if((m==task_plan1.repair_car_team[i].pathpoint[numrepairback2[i]+1].y)&&(n==task_plan1.repair_car_team[i].pathpoint[numrepairback2[i]+1].x))
                                            {
                                                m_obs = true;
                                            }

                                        rowMaze.push_back((int)m_obs);
                                        std::cout<<rowMaze.back();
                                        m_obs = false;
                                    }
                                    std::cout<<std::endl;
                                    maze.push_back(rowMaze);

                                }
                                if(task_plan1.repair_car_team[i].m_X!=1||
                                        task_plan1.repair_car_team[i].m_Y!=2)
                                {
                                    task_plan1.repair_car_team[i].astar.InitAstar(maze);
                                    task_plan1.repair_car_team[i].findpath_astar(task_plan1.repair_car_team[i].m_Y, task_plan1.repair_car_team[i].m_X, 2, 1);


                                    task_plan1.repair_car_team[i].m_X=task_plan1.repair_car_team[i].pathpoint[numrepairback2[i]].x;
                                    task_plan1.repair_car_team[i].m_Y=task_plan1.repair_car_team[i].pathpoint[numrepairback2[i]].y;
                                    numrepairback2[i]=0;//每次取规划路径的第一个点
                                }

                            }
                            continue;
                        }


                        if(clearfinish[stone_table[task_plan1.repair_car_team[i].task_locking[j]]] == 1)
                        {
                            /*前方有清理车*/
                            for(int r = 0; r < clear_car_num; r++)
                                if(
                                        numrepair2[i]<task_plan1.repair_car_team[i].count
                                        &&task_plan1.repair_car_team[i].pathpoint[2].y==(task_plan1.clear_car_team[r].m_Y)
                                        &&task_plan1.repair_car_team[i].pathpoint[2].x==task_plan1.clear_car_team[r].m_X
                                        &&!task_plan1.clear_car_team[r].disappear)
                                {
                                    wait_flag=true;
                                    break;
                                }

                            /*前方有炸弹车*/
                            for(int r = 0; r < bomb_car_num; r++)
                                if(numrepair2[i]<task_plan1.repair_car_team[i].count
                                        &&task_plan1.repair_car_team[i].pathpoint[2].y==(task_plan1.bomb_car_team[r].m_Y)
                                        &&task_plan1.repair_car_team[i].pathpoint[2].x==task_plan1.bomb_car_team[r].m_X
                                        &&!task_plan1.bomb_car_team[r].disappear)
                                {
                                    wait_flag=true;
                                    break;
                                }
                            /*前方有运输车*/
                            for(int r = 0; r < trans_car_num; r++)
                                if(numrepair2[i]<task_plan1.repair_car_team[i].count
                                        &&task_plan1.repair_car_team[i].pathpoint[2].y==(task_plan1.trans_car_team[r].m_Y)
                                        &&task_plan1.repair_car_team[i].pathpoint[2].x==task_plan1.trans_car_team[r].m_X
                                        &&!task_plan1.trans_car_team[r].disappear)
                                {
                                    wait_flag=true;
                                    break;
                                }

                            /*前方有运输车*/
                            for(int r = 0; r < repair_car_num; r++)
                                if(numrepair2[i]<task_plan1.repair_car_team[i].count
                                        &&task_plan1.repair_car_team[i].pathpoint[2].y==(task_plan1.repair_car_team[r].m_Y)
                                        &&task_plan1.repair_car_team[i].pathpoint[2].x==task_plan1.repair_car_team[r].m_X
                                        &&!task_plan1.repair_car_team[r].disappear)
                                {
                                    wait_flag=true;
                                    break;
                                }

                            if(task_plan1.repair_car_team[i].pathpoint[2].y==2
                                    &&task_plan1.repair_car_team[i].pathpoint[2].x==1)
                                wait_flag=false;


                            maze.clear();
                            for(int m=0; m<60; m++)
                            {
                                std::vector<int> rowMaze;
                                rowMaze.clear();
                                for(int n=0; n<80; n++)
                                {
                                    for(int k = 0; k < obstacle_num; k++)
                                    {
                                        if(((m>=obs_y[obs_table[k]])&&(m<(obs_y[obs_table[k]]+obs_comp[obs_table[k]]))) && ((n>=obs_x[obs_table[k]])&&(n<(obs_x[obs_table[k]]+obs_comp[obs_table[k]]))) && (task_plan1.obstacle_team[k].isfinish != 2))
                                        {
                                            m_obs = true;
                                        }
                                    }

                                    for(int p = 0; p < stone_see_num; p++)
                                    {
                                        if(((m>=stone_y[stone_table[p]])&&(m<(stone_y[stone_table[p]]+stone_comp[stone_table[p]]))) && ((n>=stone_x[stone_table[p]])&&(n<(stone_x[stone_table[p]]+stone_comp[stone_table[p]]))) && (task_plan1.stone_team[p].isfinish != 2))
                                        {
                                            m_obs = true;
                                        }
                                    }
                                    for(int l = 0; l < bomb_see_num; l++)
                                    {
                                        if(((m>=bomb_y[bomb_table[l]])&&(m<(bomb_y[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && ((n>=bomb_x[bomb_table[l]])&&(n<(bomb_x[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && (task_plan1.bomb_team[l].isfinish != 2))
                                        {
                                            m_obs = true;
                                        }
                                    }

                                    if((m==stone_y[stone_table[task_plan1.repair_car_team[i].task_locking2[j]]])&&(n==stone_x[stone_table[task_plan1.repair_car_team[i].task_locking2[j]]]))
                                    {
                                        m_obs = false;
                                    }
                                    if(wait_flag)

                                        if((m==task_plan1.repair_car_team[i].pathpoint[2].y)&&(n==task_plan1.repair_car_team[i].pathpoint[2].x))
                                        {
                                            m_obs = true;
                                        }

                                    rowMaze.push_back((int)m_obs);
                                    std::cout<<rowMaze.back();
                                    m_obs = false;
                                }
                                std::cout<<std::endl;
                                maze.push_back(rowMaze);

                            }

                            task_plan1.repair_car_team[i].astar.InitAstar(maze);

                            if(!(task_plan1.repair_car_team[i].m_X==stone_x[stone_table[task_plan1.repair_car_team[i].task_locking2[j]]]
                                 &&task_plan1.repair_car_team[i].m_Y==stone_y[stone_table[task_plan1.repair_car_team[i].task_locking2[j]]]))//没到目的地

                            {
                                task_plan1.repair_car_team[i].findpath_astar(task_plan1.repair_car_team[i].m_Y, task_plan1.repair_car_team[i].m_X, stone_y[stone_table[task_plan1.repair_car_team[i].task_locking2[j]]],stone_x[stone_table[task_plan1.repair_car_team[i].task_locking2[j]]]);
                                task_plan1.repair_car_team[i].m_X=task_plan1.repair_car_team[i].pathpoint[1].x;
                                task_plan1.repair_car_team[i].m_Y=task_plan1.repair_car_team[i].pathpoint[1].y;
                                break;
                            }

                            if(numrepair2[i] ==  qCeil(5*stone_comp[stone_table[task_plan1.repair_car_team[i].task_locking2[j]]]  / (11-repair_velo[i]/10)))
                            {
                                numrepair2[i] = 0;
                                task_plan1.stone_team[task_plan1.repair_car_team[i].task_locking2[j]].isfinish2 = 2;
                                task_plan1.repair_car_team[i].path.clear();
                                continue;

                            }
                            if(task_plan1.repair_car_team[i].m_X==stone_x[stone_table[task_plan1.repair_car_team[i].task_locking2[j]]]
                                    &&task_plan1.repair_car_team[i].m_Y==stone_y[stone_table[task_plan1.repair_car_team[i].task_locking2[j]]])//到目的地
                            {
                                numrepair2[i]++;
                                break;

                            }
                        }

                    }
                }
                else
                {
                    for(int j = 0;j < task_plan1.repair_car_team[i].task_locking.size(); j++)
                    {
                        if(task_plan1.obstacle_team[task_plan1.repair_car_team[i].task_locking[j]].isfinish2 == 2)
                        {
                            repairfinish[obs_table[task_plan1.repair_car_team[i].task_locking[j]]] = 1;
                            if(j == (task_plan1.repair_car_team[i].task_locking.size() - 1))
                            {

                                /*前方有炸弹车*/
                                for(int r = 0; r < bomb_car_num; r++)
                                { int a=task_plan1.bomb_car_team[r].m_Y;
                                    int b=task_plan1.bomb_car_team[r].m_X;
                                    if(numrepairback[i]<task_plan1.repair_car_team[i].count
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback[i]+2].y==a
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback[i]+2].x==b
                                            &&!task_plan1.bomb_car_team[r].disappear)
                                    {
                                        change_routine=true;
                                        break;
                                    }
                                }
                                /*前方有运输车*/
                                for(int r = 0; r < clear_car_num; r++)
                                    if(numrepairback[i]<task_plan1.repair_car_team[i].count
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback[i]+2].y==(task_plan1.clear_car_team[r].m_Y)
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback[i]+2].x==task_plan1.clear_car_team[r].m_X
                                            &&!task_plan1.clear_car_team[r].disappear)
                                    {
                                        change_routine=true;
                                        break;
                                    }
                                /*防止清理车路线重合*/
                                for(int r = 0; r < trans_car_num; r++)
                                    if(numrepairback[i]<task_plan1.repair_car_team[i].count
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback[i]+2].y==(task_plan1.trans_car_team[r].m_Y)
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback[i]+2].x==task_plan1.trans_car_team[r].m_X
                                            &&!task_plan1.trans_car_team[r].disappear)
                                    {
                                        change_routine=true;
                                        break;
                                    }

                                for(int r = 0; r < repair_car_num; r++)
                                    if(numrepairback[i]<task_plan1.repair_car_team[i].count
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback[i]+2].y==(task_plan1.repair_car_team[r].m_Y)
                                            &&task_plan1.repair_car_team[i].pathpoint[numrepairback[i]+2].x==task_plan1.repair_car_team[r].m_X
                                            &&!task_plan1.repair_car_team[r].disappear)
                                    {
                                        change_routine=true;
                                        break;
                                    }

                                if(task_plan1.repair_car_team[i].pathpoint[numrepairback[i]+2].y==2
                                        &&task_plan1.repair_car_team[i].pathpoint[numrepairback[i]+2].x==1)
                                    change_routine=false;
                                numrepairback[i]++;

                                maze.clear();
                                for(int m=0; m<60; m++)
                                {
                                    std::vector<int> rowMaze;
                                    rowMaze.clear();
                                    for(int n=0; n<80; n++)
                                    {
                                        for(int k = 0; k < obstacle_num; k++)
                                        {
                                            if(((m>=obs_y[obs_table[k]])&&(m<(obs_y[obs_table[k]]+obs_comp[obs_table[k]]))) && ((n>=obs_x[obs_table[k]])&&(n<(obs_x[obs_table[k]]+obs_comp[obs_table[k]]))) && (task_plan1.obstacle_team[k].isfinish != 2))
                                            {
                                                m_obs = true;
                                            }
                                        }
                                        for(int p = 0; p < stone_see_num; p++)
                                        {
                                            if(((m>=stone_y[stone_table[p]])&&(m<(stone_y[stone_table[p]]+stone_comp[stone_table[p]]))) && ((n>=stone_x[stone_table[p]])&&(n<(stone_x[stone_table[p]]+stone_comp[stone_table[p]]))) && (task_plan1.stone_team[p].isfinish != 2))
                                            {
                                                m_obs = true;
                                            }
                                        }
                                        for(int l = 0; l < bomb_see_num; l++)
                                        {
                                            if(((m>=bomb_y[bomb_table[l]])&&(m<(bomb_y[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && ((n>=bomb_x[bomb_table[l]])&&(n<(bomb_x[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && (task_plan1.bomb_team[l].isfinish != 2))
                                            {
                                                m_obs = true;
                                            }
                                        }

                                        if((m==obs_y[obs_table[task_plan1.repair_car_team[i].task_locking[j]]])&&(n==obs_x[obs_table[task_plan1.repair_car_team[i].task_locking[j]]]))
                                        {
                                            m_obs = false;
                                        }

                                        if (change_routine)
                                            if((m==task_plan1.repair_car_team[i].pathpoint[numrepairback[i]+1].y)&&(n==task_plan1.repair_car_team[i].pathpoint[numrepairback[i]+1].x))
                                            {
                                                m_obs = true;
                                            }

                                        rowMaze.push_back((int)m_obs);
                                        std::cout<<rowMaze.back();
                                        m_obs = false;
                                    }
                                    std::cout<<std::endl;
                                    maze.push_back(rowMaze);

                                }
                                if(task_plan1.repair_car_team[i].m_X!=1||
                                        task_plan1.repair_car_team[i].m_Y!=2)
                                {
                                    task_plan1.repair_car_team[i].astar.InitAstar(maze);
                                    task_plan1.repair_car_team[i].findpath_astar(task_plan1.repair_car_team[i].m_Y, task_plan1.repair_car_team[i].m_X, 2, 1);


                                    task_plan1.repair_car_team[i].m_X=task_plan1.repair_car_team[i].pathpoint[numrepairback[i]].x;
                                    task_plan1.repair_car_team[i].m_Y=task_plan1.repair_car_team[i].pathpoint[numrepairback[i]].y;
                                    numrepairback[i]=0;//每次取规划路径的第一个点
                                }
                                else
                                {
                                    repair_to_home[i] = 1;
                                }
                            }
                            continue;
                        }






                        /*前方有清理车*/
                        for(int r = 0; r < clear_car_num; r++)
                            if(
                                    numrepair[i]<task_plan1.repair_car_team[i].count
                                    &&task_plan1.repair_car_team[i].pathpoint[2].y==(task_plan1.clear_car_team[r].m_Y)
                                    &&task_plan1.repair_car_team[i].pathpoint[2].x==task_plan1.clear_car_team[r].m_X
                                    &&!task_plan1.clear_car_team[r].disappear)
                            {
                                wait_flag=true;
                                break;
                            }

                        /*前方有炸弹车*/
                        for(int r = 0; r < bomb_car_num; r++)
                            if(numrepair[i]<task_plan1.repair_car_team[i].count
                                    &&task_plan1.repair_car_team[i].pathpoint[2].y==(task_plan1.bomb_car_team[r].m_Y)
                                    &&task_plan1.repair_car_team[i].pathpoint[2].x==task_plan1.bomb_car_team[r].m_X
                                    &&!task_plan1.bomb_car_team[r].disappear)
                            {
                                wait_flag=true;
                                break;
                            }
                        /*前方有运输车*/
                        for(int r = 0; r < trans_car_num; r++)
                            if(numrepair[i]<task_plan1.repair_car_team[i].count
                                    &&task_plan1.repair_car_team[i].pathpoint[2].y==(task_plan1.trans_car_team[r].m_Y)
                                    &&task_plan1.repair_car_team[i].pathpoint[2].x==task_plan1.trans_car_team[r].m_X
                                    &&!task_plan1.trans_car_team[r].disappear)
                            {
                                wait_flag=true;
                                break;
                            }

                        for(int r = 0; r < repair_car_num; r++)
                            if(numrepair[i]<task_plan1.repair_car_team[i].count
                                    &&task_plan1.repair_car_team[i].pathpoint[2].y==(task_plan1.repair_car_team[r].m_Y)
                                    &&task_plan1.repair_car_team[i].pathpoint[2].x==task_plan1.repair_car_team[r].m_X
                                    &&!task_plan1.repair_car_team[r].disappear)
                            {
                                wait_flag=true;
                                break;
                            }

                        if(task_plan1.repair_car_team[i].pathpoint[2].y==2
                                &&task_plan1.repair_car_team[i].pathpoint[2].x==1)
                            wait_flag=false;


                        maze.clear();
                        for(int m=0; m<60; m++)
                        {
                            std::vector<int> rowMaze;
                            rowMaze.clear();
                            for(int n=0; n<80; n++)
                            {
                                for(int k = 0; k < obstacle_num; k++)
                                {
                                    if(((m>=obs_y[obs_table[k]])&&(m<(obs_y[obs_table[k]]+obs_comp[obs_table[k]]))) && ((n>=obs_x[obs_table[k]])&&(n<(obs_x[obs_table[k]]+obs_comp[obs_table[k]]))) && (task_plan1.obstacle_team[k].isfinish != 2))
                                    {
                                        m_obs = true;
                                    }
                                }

                                for(int p = 0; p < stone_see_num; p++)
                                {
                                    if(((m>=stone_y[stone_table[p]])&&(m<(stone_y[stone_table[p]]+stone_comp[stone_table[p]]))) && ((n>=stone_x[stone_table[p]])&&(n<(stone_x[stone_table[p]]+stone_comp[stone_table[p]]))) && (task_plan1.stone_team[p].isfinish != 2))
                                    {
                                        m_obs = true;
                                    }
                                }
                                for(int l = 0; l < bomb_see_num; l++)
                                {
                                    if(((m>=bomb_y[bomb_table[l]])&&(m<(bomb_y[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && ((n>=bomb_x[bomb_table[l]])&&(n<(bomb_x[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && (task_plan1.bomb_team[l].isfinish != 2))
                                    {
                                        m_obs = true;
                                    }
                                }

                                if((m==obs_y[obs_table[task_plan1.repair_car_team[i].task_locking[j]]])&&(n==obs_x[obs_table[task_plan1.repair_car_team[i].task_locking[j]]]))
                                {
                                    m_obs = false;
                                }
                                if(wait_flag)

                                    if((m==task_plan1.repair_car_team[i].pathpoint[2].y)&&(n==task_plan1.repair_car_team[i].pathpoint[2].x))
                                    {
                                        m_obs = true;
                                    }

                                rowMaze.push_back((int)m_obs);
                                std::cout<<rowMaze.back();
                                m_obs = false;
                            }
                            std::cout<<std::endl;
                            maze.push_back(rowMaze);

                        }

                        task_plan1.repair_car_team[i].astar.InitAstar(maze);

                        if(!(task_plan1.repair_car_team[i].m_X==obs_x[obs_table[task_plan1.repair_car_team[i].task_locking[j]]]
                             &&task_plan1.repair_car_team[i].m_Y==obs_y[obs_table[task_plan1.repair_car_team[i].task_locking[j]]]))//没到目的地

                        {
                            task_plan1.repair_car_team[i].findpath_astar(task_plan1.repair_car_team[i].m_Y, task_plan1.repair_car_team[i].m_X, obs_y[obs_table[task_plan1.repair_car_team[i].task_locking[j]]],obs_x[obs_table[task_plan1.repair_car_team[i].task_locking[j]]]);
                            task_plan1.repair_car_team[i].m_X=task_plan1.repair_car_team[i].pathpoint[1].x;
                            task_plan1.repair_car_team[i].m_Y=task_plan1.repair_car_team[i].pathpoint[1].y;
                            break;
                        }

                        if(numrepair[i] ==  qCeil(10*obs_comp[obs_table[task_plan1.repair_car_team[i].task_locking[j]]]  / (11-repair_velo[i]/10)))
                        {
                            numrepair[i] = 0;
                            task_plan1.obstacle_team[task_plan1.repair_car_team[i].task_locking[j]].isfinish2 = 2;
                            task_plan1.repair_car_team[i].path.clear();
                            continue;

                        }
                        if(task_plan1.repair_car_team[i].m_X==obs_x[obs_table[task_plan1.repair_car_team[i].task_locking[j]]]
                                &&task_plan1.repair_car_team[i].m_Y==obs_y[obs_table[task_plan1.repair_car_team[i].task_locking[j]]])//到目的地
                        {
                            numrepair[i]++;
                            break;

                        }


                    }
                }

            }


        }



        for(int i = 0; i < bomb_car_num; i++)
        {
            bomb_time[i]++;
            if(bomb_time[i] == (11-bomb_velo[i]/10))
            {
                bomb_time[i] = 0;
                wait_flag=false;
                change_routine=false;
                for(int j = 0;j < task_plan1.bomb_car_team[i].task_locking.size(); j++)
                {
                    if(task_plan1.bomb_team[task_plan1.bomb_car_team[i].task_locking[j]].isfinish == 2)
                    {
                        bombfinish[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]] = 1;

                        if(j == (task_plan1.bomb_car_team[i].task_locking.size() - 1))
                        {
                            for(int r = 0; r < clear_car_num; r++)
                                if(numbombback[i]<task_plan1.bomb_car_team[i].count
                                        &&task_plan1.bomb_car_team[i].pathpoint[numbombback[i]+2].y==(task_plan1.clear_car_team[r].m_Y)
                                        &&task_plan1.bomb_car_team[i].pathpoint[numbombback[i]+2].x==task_plan1.clear_car_team[r].m_X
                                        &&!task_plan1.clear_car_team[r].disappear)
                                {
                                    change_routine=true;
                                    break;
                                }

                            /*前方有运输车*/
                            for(int r = 0; r < trans_car_num; r++)
                                if(numbombback[i]<task_plan1.bomb_car_team[i].count
                                        &&task_plan1.bomb_car_team[i].pathpoint[numbombback[i]+2].y==(task_plan1.trans_car_team[r].m_Y)
                                        &&task_plan1.bomb_car_team[i].pathpoint[numbombback[i]+2].x==task_plan1.trans_car_team[r].m_X
                                        &&!task_plan1.trans_car_team[r].disappear)
                                {
                                    change_routine=true;
                                    break;
                                }
                            /*防止炸弹车路线重合*/
                            for(int r = 0; r < bomb_car_num; r++)
                                if(numbombback[i]<task_plan1.bomb_car_team[i].count
                                        &&task_plan1.bomb_car_team[i].pathpoint[numbombback[i]+2].y==(task_plan1.bomb_car_team[r].m_Y)
                                        &&task_plan1.bomb_car_team[i].pathpoint[numbombback[i]+2].x==task_plan1.bomb_car_team[r].m_X
                                        &&!task_plan1.bomb_car_team[r].disappear)
                                {
                                    change_routine=true;
                                    break;
                                }
                            for(int r = 0; r < repair_car_num; r++)
                                if(numbombback[i]<task_plan1.bomb_car_team[i].count
                                        &&task_plan1.bomb_car_team[i].pathpoint[numbombback[i]+2].y==(task_plan1.repair_car_team[r].m_Y)
                                        &&task_plan1.bomb_car_team[i].pathpoint[numbombback[i]+2].x==task_plan1.repair_car_team[r].m_X
                                        &&!task_plan1.repair_car_team[r].disappear)
                                {
                                    change_routine=true;
                                    break;
                                }

                            if(task_plan1.bomb_car_team[i].pathpoint[numbombback[i]+2].y==2
                                    &&task_plan1.bomb_car_team[i].pathpoint[numbombback[i]+2].x==1)
                                change_routine=false;


                            numbombback[i]++;

                            maze.clear();
                            for(int m=0; m<60; m++)
                            {
                                std::vector<int> rowMaze;
                                rowMaze.clear();
                                for(int n=0; n<80; n++)
                                {
                                    for(int k = 0; k < bomb_see_num; k++)
                                    {
                                        if(((m>=bomb_y[bomb_table[k]])&&(m<(bomb_y[bomb_table[k]]+bomb_comp[bomb_table[k]]))) && ((n>=bomb_x[bomb_table[k]])&&(n<(bomb_x[bomb_table[k]]+bomb_comp[bomb_table[k]]))) && (task_plan1.bomb_team[k].isfinish != 2))
                                        {
                                            m_obs = true;
                                        }
                                    }


                                    for(int p = 0; p < obstacle_num; p++)
                                    {
                                        if(((m>=obs_y[obs_table[p]])&&(m<(obs_y[obs_table[p]]+obs_comp[obs_table[p]]))) && ((n>=obs_x[obs_table[p]])&&(n<(obs_x[obs_table[p]]+obs_comp[obs_table[p]]))) && (task_plan1.obstacle_team[p].isfinish != 2))
                                        {
                                            m_obs = true;
                                        }
                                    }
                                    for(int l = 0; l < stone_see_num; l++)
                                    {
                                        if(((m>=stone_y[stone_table[l]])&&(m<(stone_y[stone_table[l]]+stone_comp[stone_table[l]]))) && ((n>=stone_x[stone_table[l]])&&(n<(stone_x[stone_table[l]]+stone_comp[stone_table[l]]))) && (task_plan1.stone_team[l].isfinish != 2))
                                        {
                                            m_obs = true;
                                        }
                                    }

                                    if((m==bomb_y[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]])&&(n==bomb_x[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]))
                                    {
                                        m_obs = false;
                                    }

                                    if (change_routine)
                                        if((m==task_plan1.bomb_car_team[i].pathpoint[numbombback[i]+1].y)&&(n==task_plan1.bomb_car_team[i].pathpoint[numbombback[i]+1].x))
                                        {
                                            m_obs = true;
                                        }


                                    rowMaze.push_back((int)m_obs);
                                    std::cout<<rowMaze.back();
                                    m_obs = false;
                                }
                                std::cout<<std::endl;
                                maze.push_back(rowMaze);

                            }

                            if(task_plan1.bomb_car_team[i].m_X!=1||
                                    task_plan1.bomb_car_team[i].m_Y!=2)
                            {
                                task_plan1.bomb_car_team[i].astar.InitAstar(maze);
                                task_plan1.bomb_car_team[i].findpath_astar(task_plan1.bomb_car_team[i].m_Y, task_plan1.bomb_car_team[i].m_X, 2, 1);


                                task_plan1.bomb_car_team[i].m_X=task_plan1.bomb_car_team[i].pathpoint[numbombback[i]].x;
                                task_plan1.bomb_car_team[i].m_Y=task_plan1.bomb_car_team[i].pathpoint[numbombback[i]].y;
                                numbombback[i]=0;//每次取规划路径的第一个点
                            }

                        }
                        continue;
                    }


                    if(stone_y[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]<bomb_y[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]
                            &&bomb_y[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]<stone_y[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]+stone_comp[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]
                            &&stone_x[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]<bomb_x[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]
                            &&bomb_x[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]<stone_x[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]+stone_comp[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]
                            &&clearfinish[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]!=1)//当前要工作的炸弹任务点的被包围,且该点障碍物任务未完成
                    {

                        bombfinish[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]] = 2;//完成标志置2被石头包围

                        break;
                    }


                    else
                    {
                        /*前方有清理车*/
                        for(int r = 0; r < clear_car_num; r++)
                            if(numbomb[i]<task_plan1.bomb_car_team[i].count
                                    &&task_plan1.bomb_car_team[i].pathpoint[2].y==(task_plan1.clear_car_team[r].m_Y)
                                    &&task_plan1.bomb_car_team[i].pathpoint[2].x==task_plan1.clear_car_team[r].m_X
                                    &&!task_plan1.clear_car_team[r].disappear)
                            {
                                wait_flag=true;

                                break;
                            }

                        /*前方有运输车*/
                        for(int r = 0; r < trans_car_num; r++)
                            if(numbomb[i]<task_plan1.bomb_car_team[i].count
                                    &&task_plan1.bomb_car_team[i].pathpoint[2].y==(task_plan1.trans_car_team[r].m_Y)
                                    &&task_plan1.bomb_car_team[i].pathpoint[2].x==task_plan1.trans_car_team[r].m_X
                                    &&!task_plan1.trans_car_team[r].disappear)
                            {
                                wait_flag=true;
                                break;
                            }

                        /*前方有炸弹车*/
                        for(int r = 0; r < bomb_car_num; r++)
                            if(numbomb[i]<task_plan1.bomb_car_team[i].count
                                    &&task_plan1.bomb_car_team[i].pathpoint[2].y==(task_plan1.bomb_car_team[r].m_Y)
                                    &&task_plan1.bomb_car_team[i].pathpoint[2].x==task_plan1.bomb_car_team[r].m_X
                                    &&!task_plan1.bomb_car_team[r].disappear)
                            {
                                wait_flag=true;
                                break;
                            }

                        for(int r = 0; r < repair_car_num; r++)
                            if(numbomb[i]<task_plan1.bomb_car_team[i].count
                                    &&task_plan1.bomb_car_team[i].pathpoint[2].y==(task_plan1.repair_car_team[r].m_Y)
                                    &&task_plan1.bomb_car_team[i].pathpoint[2].x==task_plan1.repair_car_team[r].m_X
                                    &&!task_plan1.repair_car_team[r].disappear)
                            {
                                wait_flag=true;
                                break;
                            }


                        if(task_plan1.bomb_car_team[i].pathpoint[2].y==2&&
                                task_plan1.bomb_car_team[i].pathpoint[2].x==1)
                            wait_flag=false;

                        maze.clear();
                        for(int m=0; m<60; m++)
                        {
                            std::vector<int> rowMaze;
                            rowMaze.clear();
                            for(int n=0; n<80; n++)
                            {
                                for(int k = 0; k < bomb_see_num; k++)
                                {
                                    if(((m>=bomb_y[bomb_table[k]])&&(m<(bomb_y[bomb_table[k]]+bomb_comp[bomb_table[k]]))) && ((n>=bomb_x[bomb_table[k]])&&(n<(bomb_x[bomb_table[k]]+bomb_comp[bomb_table[k]]))) && (task_plan1.bomb_team[k].isfinish != 2))
                                    {
                                        m_obs = true;
                                    }
                                }
                                for(int p = 0; p < obstacle_num; p++)
                                {
                                    if(((m>=obs_y[obs_table[p]])&&(m<(obs_y[obs_table[p]]+obs_comp[obs_table[p]]))) && ((n>=obs_x[obs_table[p]])&&(n<(obs_x[obs_table[p]]+obs_comp[obs_table[p]]))) && (task_plan1.obstacle_team[p].isfinish != 2))
                                    {
                                        m_obs = true;
                                    }
                                }
                                for(int l = 0; l < stone_see_num; l++)
                                {
                                    if(((m>=stone_y[stone_table[l]])&&(m<(stone_y[stone_table[l]]+stone_comp[stone_table[l]]))) && ((n>=stone_x[stone_table[l]])&&(n<(stone_x[stone_table[l]]+stone_comp[stone_table[l]]))) && (task_plan1.stone_team[l].isfinish != 2))
                                    {
                                        m_obs = true;
                                    }
                                }

                                if((m==bomb_y[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]])&&(n==bomb_x[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]))
                                {
                                    m_obs = false;
                                }

                                if(wait_flag)
                                    if((m==task_plan1.bomb_car_team[i].pathpoint[2].y)&&(n==task_plan1.bomb_car_team[i].pathpoint[2].x))
                                    {
                                        m_obs = true;
                                    }
                                rowMaze.push_back((int)m_obs);
                                std::cout<<rowMaze.back();
                                m_obs = false;
                            }
                            std::cout<<std::endl;
                            maze.push_back(rowMaze);

                        }

                        task_plan1.bomb_car_team[i].astar.InitAstar(maze);
                        if(!(task_plan1.bomb_car_team[i].m_X==bomb_x[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]
                             &&task_plan1.bomb_car_team[i].m_Y==bomb_y[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]))//没到目的地
                        {
                            task_plan1.bomb_car_team[i].findpath_astar(task_plan1.bomb_car_team[i].m_Y, task_plan1.bomb_car_team[i].m_X, bomb_y[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]],bomb_x[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]);
                            task_plan1.bomb_car_team[i].m_X=task_plan1.bomb_car_team[i].pathpoint[1].x;
                            task_plan1.bomb_car_team[i].m_Y=task_plan1.bomb_car_team[i].pathpoint[1].y;
                            break;
                        }



                        if(numbomb[i] >=  qCeil(50*bomb_comp[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]] / bomb_effi[i] / (11 - bomb_velo[i]/10)))
                        {
                            numbomb[i] = 0;
                            task_plan1.bomb_team[task_plan1.bomb_car_team[i].task_locking[j]].isfinish = 2;
                            task_plan1.bomb_car_team[i].path.clear();
                            continue;

                        }

                        if(task_plan1.bomb_car_team[i].m_X==bomb_x[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]]
                                &&task_plan1.bomb_car_team[i].m_Y==bomb_y[bomb_table[task_plan1.bomb_car_team[i].task_locking[j]]])//没到目的地
                        {
                            numbomb[i]++;
                            break;
                        }




                    }

                }
            }

        }





        for(int i = 0; i < clear_car_num; i++)
        {
            clear_time[i]++;
            if(clear_time[i] == (11-clear_velo[i]/10))
            {
                clear_time[i] = 0;
                wait_flag=false;
                change_routine=false;
                for(int j = 0;j < task_plan1.clear_car_team[i].task_locking.size(); j++)
                {
                    if(task_plan1.stone_team[task_plan1.clear_car_team[i].task_locking[j]].isfinish == 2)
                    {

                        clearfinish[stone_table[task_plan1.clear_car_team[i].task_locking[j]]] = 1;



                        if(j == (task_plan1.clear_car_team[i].task_locking.size() - 1))
                        {
                            /*前方有炸弹车*/
                            for(int r = 0; r < bomb_car_num; r++)
                            { int a=task_plan1.bomb_car_team[r].m_Y;
                                int b=task_plan1.bomb_car_team[r].m_X;
                                if(numclearback[i]<task_plan1.clear_car_team[i].count
                                        &&task_plan1.clear_car_team[i].pathpoint[numclearback[i]+2].y==a
                                        &&task_plan1.clear_car_team[i].pathpoint[numclearback[i]+2].x==b
                                        &&!task_plan1.bomb_car_team[r].disappear)
                                {
                                    change_routine=true;
                                    break;
                                }
                            }
                            /*前方有运输车*/
                            for(int r = 0; r < trans_car_num; r++)
                                if(numclearback[i]<task_plan1.clear_car_team[i].count
                                        &&task_plan1.clear_car_team[i].pathpoint[numclearback[i]+2].y==(task_plan1.trans_car_team[r].m_Y)
                                        &&task_plan1.clear_car_team[i].pathpoint[numclearback[i]+2].x==task_plan1.trans_car_team[r].m_X
                                        &&!task_plan1.trans_car_team[r].disappear)
                                {
                                    change_routine=true;
                                    break;
                                }
                            /*防止清理车路线重合*/
                            for(int r = 0; r < clear_car_num; r++)
                                if(numclearback[i]<task_plan1.clear_car_team[i].count
                                        &&task_plan1.clear_car_team[i].pathpoint[numclearback[i]+2].y==(task_plan1.clear_car_team[r].m_Y)
                                        &&task_plan1.clear_car_team[i].pathpoint[numclearback[i]+2].x==task_plan1.clear_car_team[r].m_X
                                        &&!task_plan1.clear_car_team[r].disappear)
                                {
                                    change_routine=true;
                                    break;
                                }
                            for(int r = 0; r < repair_car_num; r++)
                                if(numclearback[i]<task_plan1.clear_car_team[i].count
                                        &&task_plan1.clear_car_team[i].pathpoint[numclearback[i]+2].y==(task_plan1.repair_car_team[r].m_Y)
                                        &&task_plan1.clear_car_team[i].pathpoint[numclearback[i]+2].x==task_plan1.repair_car_team[r].m_X
                                        &&!task_plan1.repair_car_team[r].disappear)
                                {
                                    change_routine=true;
                                    break;
                                }
                            if(task_plan1.clear_car_team[i].pathpoint[numclearback[i]+2].y==2
                                    &&task_plan1.clear_car_team[i].pathpoint[numclearback[i]+2].x==1)
                                change_routine=false;
                            numclearback[i]++;

                            maze.clear();
                            for(int m=0; m<60; m++)
                            {
                                std::vector<int> rowMaze;
                                rowMaze.clear();
                                for(int n=0; n<80; n++)
                                {
                                    for(int k = 0; k < stone_see_num; k++)
                                    {
                                        if(((m>=stone_y[stone_table[k]])&&(m<(stone_y[stone_table[k]]+stone_comp[stone_table[k]]))) && ((n>=stone_x[stone_table[k]])&&(n<(stone_x[stone_table[k]]+stone_comp[stone_table[k]]))) && (task_plan1.stone_team[k].isfinish != 2))
                                        {
                                            m_obs = true;
                                        }
                                    }

                                    for(int p = 0; p < obstacle_num; p++)
                                    {
                                        if(((m>=obs_y[obs_table[p]])&&(m<(obs_y[obs_table[p]]+obs_comp[obs_table[p]]))) && ((n>=obs_x[obs_table[p]])&&(n<(obs_x[obs_table[p]]+obs_comp[obs_table[p]]))) && (task_plan1.obstacle_team[p].isfinish != 2))
                                        {
                                            m_obs = true;
                                        }
                                    }
                                    for(int l = 0; l < bomb_see_num; l++)
                                    {
                                        if(((m>=bomb_y[bomb_table[l]])&&(m<(bomb_y[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && ((n>=bomb_x[bomb_table[l]])&&(n<(bomb_x[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && (task_plan1.bomb_team[l].isfinish != 2))
                                        {
                                            m_obs = true;
                                        }
                                    }

                                    if((m==stone_y[stone_table[task_plan1.clear_car_team[i].task_locking[j]]])&&(n==stone_x[stone_table[task_plan1.clear_car_team[i].task_locking[j]]]))
                                    {
                                        m_obs = false;
                                    }
                                    if (change_routine)
                                        if((m==task_plan1.clear_car_team[i].pathpoint[numclearback[i]+1].y)&&(n==task_plan1.clear_car_team[i].pathpoint[numclearback[i]+1].x))
                                        {
                                            m_obs = true;
                                        }

                                    rowMaze.push_back((int)m_obs);
                                    std::cout<<rowMaze.back();
                                    m_obs = false;
                                }
                                std::cout<<std::endl;
                                maze.push_back(rowMaze);

                            }
                            if(task_plan1.clear_car_team[i].m_X!=1||
                                    task_plan1.clear_car_team[i].m_Y!=2)
                            {
                                task_plan1.clear_car_team[i].astar.InitAstar(maze);
                                task_plan1.clear_car_team[i].findpath_astar(task_plan1.clear_car_team[i].m_Y, task_plan1.clear_car_team[i].m_X, 2, 1);


                                task_plan1.clear_car_team[i].m_X=task_plan1.clear_car_team[i].pathpoint[numclearback[i]].x;
                                task_plan1.clear_car_team[i].m_Y=task_plan1.clear_car_team[i].pathpoint[numclearback[i]].y;
                                numclearback[i]=0;//每次取规划路径的第一个点
                            }

                        }
                        continue;
                    }


                    if(bombfinish[stone_table[task_plan1.clear_car_team[i].task_locking[j]]] == 1
                            ||bombfinish[stone_table[task_plan1.clear_car_team[i].task_locking[j]]] == 2)
                    {
                        /*前方有炸弹车*/
                        for(int r = 0; r < bomb_car_num; r++)
                            if(numclear[i]<task_plan1.bomb_car_team[i].count
                                    &&task_plan1.clear_car_team[i].pathpoint[2].y==(task_plan1.bomb_car_team[r].m_Y)
                                    &&task_plan1.clear_car_team[i].pathpoint[2].x==task_plan1.bomb_car_team[r].m_X
                                    &&!task_plan1.bomb_car_team[r].disappear)
                            {
                                wait_flag=true;

                                break;
                            }

                        /*前方有运输车*/
                        for(int r = 0; r < trans_car_num; r++)
                            if(numclear[i]<task_plan1.clear_car_team[i].count
                                    &&task_plan1.clear_car_team[i].pathpoint[2].y==(task_plan1.trans_car_team[r].m_Y)
                                    &&task_plan1.clear_car_team[i].pathpoint[2].x==task_plan1.trans_car_team[r].m_X
                                    &&!task_plan1.trans_car_team[r].disappear)
                            {
                                wait_flag=true;
                                break;
                            }

                        /*前方有清理车*/

                        for(int r = 0; r < clear_car_num; r++)
                            if(numclear[i]<task_plan1.clear_car_team[i].count
                                    &&task_plan1.clear_car_team[i].pathpoint[2].y==(task_plan1.clear_car_team[r].m_Y)
                                    &&task_plan1.clear_car_team[i].pathpoint[2].x==task_plan1.clear_car_team[r].m_X
                                    &&!task_plan1.clear_car_team[r].disappear)
                            {
                                wait_flag=true;
                                break;
                            }

                        for(int r = 0; r < repair_car_num; r++)
                            if(numclear[i]<task_plan1.clear_car_team[i].count
                                    &&task_plan1.clear_car_team[i].pathpoint[2].y==(task_plan1.repair_car_team[r].m_Y)
                                    &&task_plan1.clear_car_team[i].pathpoint[2].x==task_plan1.repair_car_team[r].m_X
                                    &&!task_plan1.repair_car_team[r].disappear)
                            {
                                wait_flag=true;
                                break;
                            }



                        if(task_plan1.bomb_car_team[i].pathpoint[2].y==2&&
                                task_plan1.bomb_car_team[i].pathpoint[2].x==1)
                            wait_flag=false;

                        maze.clear();
                        for(int m=0; m<60; m++)
                        {
                            std::vector<int> rowMaze;
                            rowMaze.clear();
                            for(int n=0; n<80; n++)
                            {
                                for(int k = 0; k < bomb_see_num; k++)
                                {
                                    if(((m>=bomb_y[bomb_table[k]])&&(m<(bomb_y[bomb_table[k]]+bomb_comp[bomb_table[k]]))) && ((n>=bomb_x[bomb_table[k]])&&(n<(bomb_x[bomb_table[k]]+bomb_comp[bomb_table[k]]))) && (task_plan1.bomb_team[k].isfinish != 2))
                                    {
                                        m_obs = true;
                                    }
                                }
                                for(int p = 0; p < obstacle_num; p++)
                                {
                                    if(((m>=obs_y[obs_table[p]])&&(m<(obs_y[obs_table[p]]+obs_comp[obs_table[p]]))) && ((n>=obs_x[obs_table[p]])&&(n<(obs_x[obs_table[p]]+obs_comp[obs_table[p]]))) && (task_plan1.obstacle_team[p].isfinish != 2))
                                    {
                                        m_obs = true;
                                    }
                                }
                                for(int l = 0; l < stone_see_num; l++)
                                {
                                    if(((m>=stone_y[stone_table[l]])&&(m<(stone_y[stone_table[l]]+stone_comp[stone_table[l]]))) && ((n>=stone_x[stone_table[l]])&&(n<(stone_x[stone_table[l]]+stone_comp[stone_table[l]]))) && (task_plan1.stone_team[l].isfinish != 2))
                                    {
                                        m_obs = true;
                                    }
                                }

                                if((m==stone_y[stone_table[task_plan1.clear_car_team[i].task_locking[j]]])&&(n==stone_x[stone_table[task_plan1.clear_car_team[i].task_locking[j]]]))
                                {
                                    m_obs = false;
                                }

                                if(wait_flag)
                                    if((m==task_plan1.clear_car_team[i].pathpoint[2].y)&&(n==task_plan1.clear_car_team[i].pathpoint[2].x))
                                    {
                                        m_obs = true;
                                    }
                                rowMaze.push_back((int)m_obs);
                                std::cout<<rowMaze.back();
                                m_obs = false;
                            }
                            std::cout<<std::endl;
                            maze.push_back(rowMaze);

                        }

                        task_plan1.clear_car_team[i].astar.InitAstar(maze);

                        if(!(task_plan1.clear_car_team[i].m_X==stone_x[stone_table[task_plan1.clear_car_team[i].task_locking[j]]]
                             &&task_plan1.clear_car_team[i].m_Y==stone_y[stone_table[task_plan1.clear_car_team[i].task_locking[j]]]))//没到目的地

                        {
                            task_plan1.clear_car_team[i].findpath_astar(task_plan1.clear_car_team[i].m_Y, task_plan1.clear_car_team[i].m_X, stone_y[stone_table[task_plan1.clear_car_team[i].task_locking[j]]],stone_x[stone_table[task_plan1.clear_car_team[i].task_locking[j]]]);
                            task_plan1.clear_car_team[i].m_X=task_plan1.clear_car_team[i].pathpoint[1].x;
                            task_plan1.clear_car_team[i].m_Y=task_plan1.clear_car_team[i].pathpoint[1].y;
                            break;
                        }



                        if(numclear[i] ==  qCeil(50*stone_comp[stone_table[task_plan1.clear_car_team[i].task_locking[j]]] / clear_effi[i] / (11-clear_velo[i]/10)))
                        {
                            numclear[i] = 0;
                            task_plan1.stone_team[task_plan1.clear_car_team[i].task_locking[j]].isfinish = 2;
                            task_plan1.clear_car_team[i].path.clear();
                            continue;

                        }
                        if(task_plan1.clear_car_team[i].m_X==stone_x[stone_table[task_plan1.clear_car_team[i].task_locking[j]]]
                                &&task_plan1.clear_car_team[i].m_Y==stone_y[stone_table[task_plan1.clear_car_team[i].task_locking[j]]])//没到目的地
                        {
                            numclear[i]++;
                            break;
                        }
                    }

                }

            }


        }




        for(int i = 0; i < trans_car_num; i++)
        {
            trans_time[i]++;
            if(trans_time[i] == (11-trans_velo[i]/10))
            {
                trans_time[i] = 0;
                wait_flag=false;
                change_routine=false;
                for(int j = 0;j < task_plan1.trans_car_team[i].task_locking.size(); j++)
                {
                    if(task_plan1.obstacle_team[task_plan1.trans_car_team[i].task_locking[j]].isfinish == 2)
                    {
                        if(j == (task_plan1.trans_car_team[i].task_locking.size() - 1))
                        {
                            /*前方有炸弹车*/
                            for(int r = 0; r < bomb_car_num; r++)
                            { int a=task_plan1.bomb_car_team[r].m_Y;
                                int b=task_plan1.bomb_car_team[r].m_X;
                                if(num1back[i]<task_plan1.trans_car_team[i].count
                                        &&task_plan1.trans_car_team[i].pathpoint[num1back[i]+2].y==a
                                        &&task_plan1.trans_car_team[i].pathpoint[num1back[i]+2].x==b
                                        &&!task_plan1.bomb_car_team[r].disappear)
                                {
                                    change_routine=true;
                                    break;
                                }
                            }
                            /*前方有运输车*/
                            for(int r = 0; r < clear_car_num; r++)
                                if(num1back[i]<task_plan1.trans_car_team[i].count
                                        &&task_plan1.trans_car_team[i].pathpoint[num1back[i]+2].y==(task_plan1.clear_car_team[r].m_Y)
                                        &&task_plan1.trans_car_team[i].pathpoint[num1back[i]+2].x==task_plan1.clear_car_team[r].m_X
                                        &&!task_plan1.clear_car_team[r].disappear)
                                {
                                    change_routine=true;
                                    break;
                                }
                            /*防止清理车路线重合*/
                            for(int r = 0; r < trans_car_num; r++)
                                if(num1back[i]<task_plan1.trans_car_team[i].count
                                        &&task_plan1.trans_car_team[i].pathpoint[num1back[i]+2].y==(task_plan1.trans_car_team[r].m_Y)
                                        &&task_plan1.trans_car_team[i].pathpoint[num1back[i]+2].x==task_plan1.trans_car_team[r].m_X
                                        &&!task_plan1.trans_car_team[r].disappear)
                                {
                                    change_routine=true;
                                    break;
                                }

                            for(int r = 0; r < repair_car_num; r++)
                                if(num1back[i]<task_plan1.trans_car_team[i].count
                                        &&task_plan1.trans_car_team[i].pathpoint[num1back[i]+2].y==(task_plan1.repair_car_team[r].m_Y)
                                        &&task_plan1.trans_car_team[i].pathpoint[num1back[i]+2].x==task_plan1.repair_car_team[r].m_X
                                        &&!task_plan1.repair_car_team[r].disappear)
                                {
                                    change_routine=true;
                                    break;
                                }
                            if(task_plan1.trans_car_team[i].pathpoint[num1back[i]+2].y==2
                                    &&task_plan1.trans_car_team[i].pathpoint[num1back[i]+2].x==1)
                                change_routine=false;
                            num1back[i]++;

                            maze.clear();
                            for(int m=0; m<60; m++)
                            {
                                std::vector<int> rowMaze;
                                rowMaze.clear();
                                for(int n=0; n<80; n++)
                                {
                                    for(int k = 0; k < obstacle_num; k++)
                                    {
                                        if(((m>=obs_y[obs_table[k]])&&(m<(obs_y[obs_table[k]]+obs_comp[obs_table[k]]))) && ((n>=obs_x[obs_table[k]])&&(n<(obs_x[obs_table[k]]+obs_comp[obs_table[k]]))) && (task_plan1.obstacle_team[k].isfinish != 2))
                                        {
                                            m_obs = true;
                                        }
                                    }
                                    for(int p = 0; p < stone_see_num; p++)
                                    {
                                        if(((m>=stone_y[stone_table[p]])&&(m<(stone_y[stone_table[p]]+stone_comp[stone_table[p]]))) && ((n>=stone_x[stone_table[p]])&&(n<(stone_x[stone_table[p]]+stone_comp[stone_table[p]]))) && (task_plan1.stone_team[p].isfinish != 2))
                                        {
                                            m_obs = true;
                                        }
                                    }
                                    for(int l = 0; l < bomb_see_num; l++)
                                    {
                                        if(((m>=bomb_y[bomb_table[l]])&&(m<(bomb_y[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && ((n>=bomb_x[bomb_table[l]])&&(n<(bomb_x[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && (task_plan1.bomb_team[l].isfinish != 2))
                                        {
                                            m_obs = true;
                                        }
                                    }

                                    if((m==obs_y[obs_table[task_plan1.trans_car_team[i].task_locking[j]]])&&(n==obs_x[obs_table[task_plan1.trans_car_team[i].task_locking[j]]]))
                                    {
                                        m_obs = false;
                                    }

                                    if (change_routine)
                                        if((m==task_plan1.trans_car_team[i].pathpoint[num1back[i]+1].y)&&(n==task_plan1.trans_car_team[i].pathpoint[num1back[i]+1].x))
                                        {
                                            m_obs = true;
                                        }

                                    rowMaze.push_back((int)m_obs);
                                    std::cout<<rowMaze.back();
                                    m_obs = false;
                                }
                                std::cout<<std::endl;
                                maze.push_back(rowMaze);

                            }
                            if(task_plan1.trans_car_team[i].m_X!=1||
                                    task_plan1.trans_car_team[i].m_Y!=2)
                            {
                                task_plan1.trans_car_team[i].astar.InitAstar(maze);
                                task_plan1.trans_car_team[i].findpath_astar(task_plan1.trans_car_team[i].m_Y, task_plan1.trans_car_team[i].m_X, 2, 1);


                                task_plan1.trans_car_team[i].m_X=task_plan1.trans_car_team[i].pathpoint[num1back[i]].x;
                                task_plan1.trans_car_team[i].m_Y=task_plan1.trans_car_team[i].pathpoint[num1back[i]].y;
                                num1back[i]=0;//每次取规划路径的第一个点
                            }
                        }
                        continue;
                    }

                    if((clearfinish[obs_table[task_plan1.trans_car_team[i].task_locking[j]]] == 1) && (bombfinish[obs_table[task_plan1.trans_car_team[i].task_locking[j]]] == 1)
                            &&repairfinish[obs_table[task_plan1.trans_car_team[i].task_locking[j]]] == 1)
                    {
                        /*前方有清理车*/
                        for(int r = 0; r < clear_car_num; r++)
                            if(
                                    num1[i]<task_plan1.trans_car_team[i].count
                                    &&task_plan1.trans_car_team[i].pathpoint[2].y==(task_plan1.clear_car_team[r].m_Y)
                                    &&task_plan1.trans_car_team[i].pathpoint[2].x==task_plan1.clear_car_team[r].m_X
                                    &&!task_plan1.clear_car_team[r].disappear)
                            {
                                wait_flag=true;
                                break;
                            }

                        /*前方有炸弹车*/
                        for(int r = 0; r < bomb_car_num; r++)
                            if(num1[i]<task_plan1.trans_car_team[i].count
                                    &&task_plan1.trans_car_team[i].pathpoint[2].y==(task_plan1.bomb_car_team[r].m_Y)
                                    &&task_plan1.trans_car_team[i].pathpoint[2].x==task_plan1.bomb_car_team[r].m_X
                                    &&!task_plan1.bomb_car_team[r].disappear)
                            {
                                wait_flag=true;
                                break;
                            }
                        /*前方有运输车*/
                        for(int r = 0; r < trans_car_num; r++)
                            if(num1[i]<task_plan1.trans_car_team[i].count
                                    &&task_plan1.trans_car_team[i].pathpoint[2].y==(task_plan1.trans_car_team[r].m_Y)
                                    &&task_plan1.trans_car_team[i].pathpoint[2].x==task_plan1.trans_car_team[r].m_X
                                    &&!task_plan1.trans_car_team[r].disappear)
                            {
                                wait_flag=true;
                                break;
                            }

                        for(int r = 0; r < repair_car_num; r++)
                            if(num1[i]<task_plan1.trans_car_team[i].count
                                    &&task_plan1.trans_car_team[i].pathpoint[2].y==(task_plan1.repair_car_team[r].m_Y)
                                    &&task_plan1.trans_car_team[i].pathpoint[2].x==task_plan1.repair_car_team[r].m_X
                                    &&!task_plan1.repair_car_team[r].disappear)
                            {
                                wait_flag=true;
                                break;
                            }
                        if(task_plan1.trans_car_team[i].pathpoint[2].y==2
                                &&task_plan1.trans_car_team[i].pathpoint[2].x==1)
                            wait_flag=false;


                        maze.clear();
                        for(int m=0; m<60; m++)
                        {
                            std::vector<int> rowMaze;
                            rowMaze.clear();
                            for(int n=0; n<80; n++)
                            {
                                for(int k = 0; k < obstacle_num; k++)
                                {
                                    if(((m>=obs_y[obs_table[k]])&&(m<(obs_y[obs_table[k]]+obs_comp[obs_table[k]]))) && ((n>=obs_x[obs_table[k]])&&(n<(obs_x[obs_table[k]]+obs_comp[obs_table[k]]))) && (task_plan1.obstacle_team[k].isfinish != 2))
                                    {
                                        m_obs = true;
                                    }
                                }

                                for(int p = 0; p < stone_see_num; p++)
                                {
                                    if(((m>=stone_y[stone_table[p]])&&(m<(stone_y[stone_table[p]]+stone_comp[stone_table[p]]))) && ((n>=stone_x[stone_table[p]])&&(n<(stone_x[stone_table[p]]+stone_comp[stone_table[p]]))) && (task_plan1.stone_team[p].isfinish != 2))
                                    {
                                        m_obs = true;
                                    }
                                }
                                for(int l = 0; l < bomb_see_num; l++)
                                {
                                    if(((m>=bomb_y[bomb_table[l]])&&(m<(bomb_y[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && ((n>=bomb_x[bomb_table[l]])&&(n<(bomb_x[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && (task_plan1.bomb_team[l].isfinish != 2))
                                    {
                                        m_obs = true;
                                    }
                                }

                                if((m==obs_y[obs_table[task_plan1.trans_car_team[i].task_locking[j]]])&&(n==obs_x[obs_table[task_plan1.trans_car_team[i].task_locking[j]]]))
                                {
                                    m_obs = false;
                                }
                                if(wait_flag)

                                    if((m==task_plan1.trans_car_team[i].pathpoint[2].y)&&(n==task_plan1.trans_car_team[i].pathpoint[2].x))
                                    {
                                        m_obs = true;
                                    }

                                rowMaze.push_back((int)m_obs);
                                std::cout<<rowMaze.back();
                                m_obs = false;
                            }
                            std::cout<<std::endl;
                            maze.push_back(rowMaze);

                        }

                        task_plan1.trans_car_team[i].astar.InitAstar(maze);

                        if(!(task_plan1.trans_car_team[i].m_X==obs_x[obs_table[task_plan1.trans_car_team[i].task_locking[j]]]
                             &&task_plan1.trans_car_team[i].m_Y==obs_y[obs_table[task_plan1.trans_car_team[i].task_locking[j]]]))//没到目的地

                        {
                            task_plan1.trans_car_team[i].findpath_astar(task_plan1.trans_car_team[i].m_Y, task_plan1.trans_car_team[i].m_X, obs_y[obs_table[task_plan1.trans_car_team[i].task_locking[j]]],obs_x[obs_table[task_plan1.trans_car_team[i].task_locking[j]]]);
                            task_plan1.trans_car_team[i].m_X=task_plan1.trans_car_team[i].pathpoint[1].x;
                            task_plan1.trans_car_team[i].m_Y=task_plan1.trans_car_team[i].pathpoint[1].y;
                            break;
                        }

                        if(num1[i] ==  qCeil(50*obs_comp[obs_table[task_plan1.trans_car_team[i].task_locking[j]]] / trans_effi[i] / (11-trans_velo[i]/10)))
                        {
                            num1[i] = 0;
                            task_plan1.obstacle_team[task_plan1.trans_car_team[i].task_locking[j]].isfinish = 2;
                            task_plan1.trans_car_team[i].path.clear();
                            continue;

                        }
                        if(task_plan1.trans_car_team[i].m_X==obs_x[obs_table[task_plan1.trans_car_team[i].task_locking[j]]]
                                &&task_plan1.trans_car_team[i].m_Y==obs_y[obs_table[task_plan1.trans_car_team[i].task_locking[j]]])//到目的地
                        {
                            num1[i]++;
                            break;

                        }
                    }

                }
            }


        }




    }

}
void gridmap::begin_run()
{
    connect(m_timer,&QTimer::timeout,[=]()
    {

        updataposition();

        update();

    });
}

void gridmap::wheelEvent(QWheelEvent *event)
{
    double numDegrees = event->delta() / 8.0;
    double numSteps = numDegrees / 15.0;
    factor *= pow(1.1, numSteps);
    if (factor < 0.07)
        factor = 0.07;
    if(factor > 50)
        factor = 50;

    qDebug() << factor << numDegrees << numSteps << event->delta();
    update();

}


void gridmap::mousePressEvent(QMouseEvent *event)
{
    m_OldPos = event->pos();
    m_Pressed = true;
}

void gridmap::mouseMoveEvent(QMouseEvent *event)
{
    if (!m_Pressed)
        return QWidget::mouseMoveEvent(event);

    this->setCursor(Qt::SizeAllCursor);
    QPoint pos = event->pos();
    int xPtInterval = pos.x() - m_OldPos.x();
    int yPtInterval = pos.y() - m_OldPos.y();

    m_XPtInterval += xPtInterval;
    m_YPtInterval += yPtInterval;

    m_OldPos = pos;
    this->update();
}

void gridmap::mouseReleaseEvent(QMouseEvent *event)
{
    m_Pressed = false;
    this->setCursor(Qt::ArrowCursor);
}


void sleep(unsigned int msec)
{
    QTime reachTime = QTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime)
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}


void gridmap::createMaze()
{


}

void gridmap::Emergency_return()
{
    for(int i = 0; i < trans_car_num; i++)
    {
        if((task_plan1.trans_car_team[i].m_Y == 2) && (task_plan1.trans_car_team[i].m_X == 1))
        {
            continue;
        }
        maze.clear();
        for(int m=0; m<60; m++)
        {
            std::vector<int> rowMaze;
            rowMaze.clear();
            for(int n=0; n<80; n++)
            {
                for(int k = 0; k < obstacle_num; k++)
                {
                    if(((m>=obs_y[obs_table[k]])&&(m<(obs_y[obs_table[k]]+obs_comp[obs_table[k]]))) && ((n>=obs_x[obs_table[k]])&&(n<(obs_x[obs_table[k]]+obs_comp[obs_table[k]]))) && (task_plan1.obstacle_team[k].isfinish != 2))
                    {
                        m_obs = true;
                    }
                }
                for(int p = 0; p < stone_see_num; p++)
                {
                    if(((m>=stone_y[stone_table[p]])&&(m<(stone_y[stone_table[p]]+stone_comp[stone_table[p]]))) && ((n>=stone_x[stone_table[p]])&&(n<(stone_x[stone_table[p]]+stone_comp[stone_table[p]]))) && (task_plan1.stone_team[p].isfinish != 2))
                    {
                        m_obs = true;
                    }
                }
                for(int l = 0; l < bomb_see_num; l++)
                {
                    if(((m>=bomb_y[bomb_table[l]])&&(m<(bomb_y[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && ((n>=bomb_x[bomb_table[l]])&&(n<(bomb_x[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && (task_plan1.bomb_team[l].isfinish != 2))
                    {
                        m_obs = true;
                    }
                }

                if((m == task_plan1.trans_car_team[i].m_Y)&&(n == task_plan1.trans_car_team[i].m_X))
                {
                    m_obs = false;
                }

                rowMaze.push_back((int)m_obs);
                std::cout<<rowMaze.back();
                m_obs = false;
            }
            std::cout<<std::endl;
            maze.push_back(rowMaze);

        }

        num1return[i]++;
        task_plan1.trans_car_team[i].astar.InitAstar(maze);
        if(num1return[i] == 1)
        {
            task_plan1.trans_car_team[i].findpath_astar(task_plan1.trans_car_team[i].m_Y, task_plan1.trans_car_team[i].m_X, 2, 1);

        }


        if(num1return[i] < task_plan1.trans_car_team[i].count)
        {
            task_plan1.trans_car_team[i].m_X=task_plan1.trans_car_team[i].pathpoint[num1return[i]].x;
            task_plan1.trans_car_team[i].m_Y=task_plan1.trans_car_team[i].pathpoint[num1return[i]].y;
        }


    }
}


void gridmap::Emergency_clear_return()
{
    for(int i = 0; i < clear_car_num; i++)
    {
        if((task_plan1.clear_car_team[i].m_Y == 2) && (task_plan1.clear_car_team[i].m_X == 1))
        {
            continue;
        }
        maze.clear();
        for(int m=0; m<60; m++)
        {
            std::vector<int> rowMaze;
            rowMaze.clear();
            for(int n=0; n<80; n++)
            {
                for(int k = 0; k < stone_see_num; k++)
                {
                    if(((m>=stone_y[stone_table[k]])&&(m<(stone_y[stone_table[k]]+stone_comp[stone_table[k]]))) && ((n>=stone_x[stone_table[k]])&&(n<(stone_x[stone_table[k]]+stone_comp[stone_table[k]]))) && (task_plan1.stone_team[k].isfinish != 2))
                    {
                        m_obs = true;
                    }
                }

                for(int p = 0; p < obstacle_num; p++)
                {
                    if(((m>=obs_y[obs_table[p]])&&(m<(obs_y[obs_table[p]]+obs_comp[obs_table[p]]))) && ((n>=obs_x[obs_table[p]])&&(n<(obs_x[obs_table[p]]+obs_comp[obs_table[p]]))) && (task_plan1.obstacle_team[p].isfinish != 2))
                    {
                        m_obs = true;
                    }
                }
                for(int l = 0; l < bomb_see_num; l++)
                {
                    if(((m>=bomb_y[bomb_table[l]])&&(m<(bomb_y[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && ((n>=bomb_x[bomb_table[l]])&&(n<(bomb_x[bomb_table[l]]+bomb_comp[bomb_table[l]]))) && (task_plan1.bomb_team[l].isfinish != 2))
                    {
                        m_obs = true;
                    }
                }

                if((m == task_plan1.clear_car_team[i].m_Y)&&(n == task_plan1.clear_car_team[i].m_X))
                {
                    m_obs = false;
                }

                rowMaze.push_back((int)m_obs);
                std::cout<<rowMaze.back();
                m_obs = false;
            }
            std::cout<<std::endl;
            maze.push_back(rowMaze);

        }

        numclearreturn[i]++;
        task_plan1.clear_car_team[i].astar.InitAstar(maze);
        if(numclearreturn[i] == 1)
        {
            task_plan1.clear_car_team[i].findpath_astar(task_plan1.clear_car_team[i].m_Y, task_plan1.clear_car_team[i].m_X, 2, 1);

        }


        if(numclearreturn[i] < task_plan1.clear_car_team[i].count)
        {
            task_plan1.clear_car_team[i].m_X=task_plan1.clear_car_team[i].pathpoint[numclearreturn[i]].x;
            task_plan1.clear_car_team[i].m_Y=task_plan1.clear_car_team[i].pathpoint[numclearreturn[i]].y;
        }


    }
}



void gridmap::Emergency_bomb_return()
{
    for(int i = 0; i < bomb_car_num; i++)
    {
        if((task_plan1.bomb_car_team[i].m_Y == 2) && (task_plan1.bomb_car_team[i].m_X == 1))
        {
            continue;
        }
        maze.clear();
        for(int m=0; m<60; m++)
        {
            std::vector<int> rowMaze;
            rowMaze.clear();
            for(int n=0; n<80; n++)
            {
                for(int k = 0; k < bomb_see_num; k++)
                {
                    if(((m>=bomb_y[bomb_table[k]])&&(m<(bomb_y[bomb_table[k]]+bomb_comp[bomb_table[k]]))) && ((n>=bomb_x[bomb_table[k]])&&(n<(bomb_x[bomb_table[k]]+bomb_comp[bomb_table[k]]))) && (task_plan1.bomb_team[k].isfinish != 2))
                    {
                        m_obs = true;
                    }
                }


                for(int p = 0; p < obstacle_num; p++)
                {
                    if(((m>=obs_y[obs_table[p]])&&(m<(obs_y[obs_table[p]]+obs_comp[obs_table[p]]))) && ((n>=obs_x[obs_table[p]])&&(n<(obs_x[obs_table[p]]+obs_comp[obs_table[p]]))) && (task_plan1.obstacle_team[p].isfinish != 2))
                    {
                        m_obs = true;
                    }
                }
                for(int l = 0; l < stone_see_num; l++)
                {
                    if(((m>=stone_y[stone_table[l]])&&(m<(stone_y[stone_table[l]]+stone_comp[stone_table[l]]))) && ((n>=stone_x[stone_table[l]])&&(n<(stone_x[stone_table[l]]+stone_comp[stone_table[l]]))) && (task_plan1.stone_team[l].isfinish != 2))
                    {
                        m_obs = true;
                    }
                }

                if((m == task_plan1.bomb_car_team[i].m_Y)&&(n == task_plan1.bomb_car_team[i].m_X))
                {
                    m_obs = false;
                }

                rowMaze.push_back((int)m_obs);
                std::cout<<rowMaze.back();
                m_obs = false;
            }
            std::cout<<std::endl;
            maze.push_back(rowMaze);

        }

        numbombreturn[i]++;
        task_plan1.bomb_car_team[i].astar.InitAstar(maze);
        if(numbombreturn[i] == 1)
        {
            task_plan1.bomb_car_team[i].findpath_astar(task_plan1.bomb_car_team[i].m_Y, task_plan1.bomb_car_team[i].m_X, 2, 1);

        }


        if(numbombreturn[i] < task_plan1.bomb_car_team[i].count)
        {
            task_plan1.bomb_car_team[i].m_X=task_plan1.bomb_car_team[i].pathpoint[numbombreturn[i]].x;
            task_plan1.bomb_car_team[i].m_Y=task_plan1.bomb_car_team[i].pathpoint[numbombreturn[i]].y;
        }


    }
}


void gridmap::Emergency_repair_return()
{
    for(int i = 0; i < repair_car_num; i++)
    {
        if((task_plan1.repair_car_team[i].m_Y == 2) && (task_plan1.repair_car_team[i].m_X == 1))
        {
            continue;
        }
        maze.clear();
        for(int m=0; m<60; m++)
        {
            std::vector<int> rowMaze;
            rowMaze.clear();
            for(int n=0; n<80; n++)
            {
                for(int k = 0; k < bomb_see_num; k++)
                {
                    if(((m>=bomb_y[bomb_table[k]])&&(m<(bomb_y[bomb_table[k]]+bomb_comp[bomb_table[k]]))) && ((n>=bomb_x[bomb_table[k]])&&(n<(bomb_x[bomb_table[k]]+bomb_comp[bomb_table[k]]))) && (task_plan1.bomb_team[k].isfinish != 2))
                    {
                        m_obs = true;
                    }
                }


                for(int p = 0; p < obstacle_num; p++)
                {
                    if(((m>=obs_y[obs_table[p]])&&(m<(obs_y[obs_table[p]]+obs_comp[obs_table[p]]))) && ((n>=obs_x[obs_table[p]])&&(n<(obs_x[obs_table[p]]+obs_comp[obs_table[p]]))) && (task_plan1.obstacle_team[p].isfinish != 2))
                    {
                        m_obs = true;
                    }
                }
                for(int l = 0; l < stone_see_num; l++)
                {
                    if(((m>=stone_y[stone_table[l]])&&(m<(stone_y[stone_table[l]]+stone_comp[stone_table[l]]))) && ((n>=stone_x[stone_table[l]])&&(n<(stone_x[stone_table[l]]+stone_comp[stone_table[l]]))) && (task_plan1.stone_team[l].isfinish != 2))
                    {
                        m_obs = true;
                    }
                }

                if((m == task_plan1.repair_car_team[i].m_Y)&&(n == task_plan1.repair_car_team[i].m_X))
                {
                    m_obs = false;
                }

                rowMaze.push_back((int)m_obs);
                std::cout<<rowMaze.back();
                m_obs = false;
            }
            std::cout<<std::endl;
            maze.push_back(rowMaze);

        }

        numrepairreturn[i]++;
        task_plan1.repair_car_team[i].astar.InitAstar(maze);
        if(numrepairreturn[i] == 1)
        {
            task_plan1.repair_car_team[i].findpath_astar(task_plan1.repair_car_team[i].m_Y, task_plan1.repair_car_team[i].m_X, 2, 1);

        }


        if(numrepairreturn[i] < task_plan1.repair_car_team[i].count)
        {
            task_plan1.repair_car_team[i].m_X=task_plan1.repair_car_team[i].pathpoint[numrepairreturn[i]].x;
            task_plan1.repair_car_team[i].m_Y=task_plan1.repair_car_team[i].pathpoint[numrepairreturn[i]].y;
        }


    }
}



void gridmap::Emergency_copter_return()
{

    for(int i=0;i<copter_num;i++)
        copter_flag[i] = 1;

    if(copter_flag2 == 0)
    {
        for(int j = 0; j < copter_num; j++)
        {
            copter_last_m_Y[j] = task_plan1.copter_team[j].m_Y;
            copter_last_m_X[j] = task_plan1.copter_team[j].m_X;
        }
        copter_flag2 = 1;
    }



    /*第一步*/
    for(int i = 0; i < copter_num; i++)
    {
        if(step1[i]==0)
        {

            if(task_plan1.copter_team[i].m_Y ==copter_path[i])
            {
                step1[i]=1;
            }

            if(task_plan1.copter_team[i].m_Y > copter_path[i])
            {

                task_plan1.copter_team[i].m_Y = task_plan1.copter_team[i].m_Y - 1;
            }

            if(task_plan1.copter_team[i].m_Y < copter_path[i])
            {

                task_plan1.copter_team[i].m_Y = task_plan1.copter_team[i].m_Y + 1;
            }
        }
    }
    /*第二步*/
    int k1=0;
    for(int i = 0; i < copter_num; i++)
    {
        if(step1[i]==1)
            k1++;

    }
    if(k1==copter_num)
        for(int i = 0; i < copter_num; i++)
        {

            if(task_plan1.copter_team[i].m_Y ==copter_path[i]
                    &&task_plan1.copter_team[i].m_X==0)
            {
                step2[i]=1;
            }

            if(task_plan1.copter_team[i].m_X > 0&&task_plan1.copter_team[i].m_Y ==copter_path[i])
            {
                task_plan1.copter_team[i].m_X = task_plan1.copter_team[i].m_X - 1;
            }




        }


    /*第三步*/
    int k2=0;
    for(int i = 0; i < copter_num; i++)
    {
        if(step2[i]==1)
            k2++;

    }

    if(k2==copter_num)//全部就位
        for(int i = 0; i < copter_num; i++)
        {
            if(task_plan1.copter_team[i].m_Y > 0)
            {

                task_plan1.copter_team[i].m_Y = task_plan1.copter_team[i].m_Y - 1;
            }

        }


}




