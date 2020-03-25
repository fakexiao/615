#include "vehicle_table.h"
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>


extern int trans_car_num;
extern int clear_car_num;
extern int bomb_car_num;
extern int repair_car_num;
extern int trans_start;
extern float trans_effi[20];
extern float bomb_effi[20];
extern float clear_effi[20];
extern float repair_effi[20];
extern int trans_velo[20];
extern int repair_velo[20];
extern int bomb_velo[20];
extern int clear_velo[20];
extern int trans_oil[20];
extern int bomb_oil[20];
extern int clear_oil[20];
extern int repair_to_home[20];

int vehicle_flag;


vehicle_table::vehicle_table(QWidget *parent)
    : QTableWidget(parent)
{

    setWindowTitle(tr("任务车辆信息"));

    setColumnCount(5);//列数

    horizontalHeader()->setStyleSheet("QHeaderView::section{background:#444444;color:white;font:bold 10pt '楷体' ;}");//行头背景

    verticalHeader()->hide();

    horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);  //表头的文字居中
    setStyleSheet(QString( "QTableWidget QHeaderView::section{background:#2a9ee4;font-weight:bold;}"));

    horizontalHeader()->setSectionResizeMode (QHeaderView::Stretch);



    QStringList header1;
    header1<<tr("任务车辆")<<tr("效率")<<tr("速度")<<tr("正在执行任务")<<tr("车辆是否遇袭");
    setHorizontalHeaderLabels(header1);


    horizontalHeader()->setMinimumHeight(50);
    verticalHeader()->setDefaultSectionSize(50); //设置行高
    setStyleSheet("QTableView::Item{background-color:#444444}");


    QToolButton *toolButton2 = new QToolButton(this); //新建toolButton
    toolButton2->setText("车辆类型"); //设置内容
    toolButton2->setPopupMode(QToolButton::InstantPopup); //设置模式 必须
    toolButton2->setFixedSize(200,52);

    toolButton2->setStyleSheet("\
        QToolButton::menu-indicator{\
        image: none;\
    }");

    QMenu * q = new QMenu(this); //创建菜单
    QAction *q1 = q->addAction("抢修车辆");
    QAction *q2 = q->addAction("清障车辆");
    QAction *q3 = q->addAction("排弹车辆");
    QAction *q4 = q->addAction("运输车辆");
    toolButton2->setMenu(q); //将菜单添加到toolButton中


    connect(q1, &QAction::triggered,
            [=]()
    {
        vehicle_flag = 1;

    });

    connect(q2, &QAction::triggered,
            [=]()
    {
        vehicle_flag = 2;

    });

    connect(q3, &QAction::triggered,
            [=]()
    {
        vehicle_flag = 3;

    });

    connect(q4, &QAction::triggered,
            [=]()
    {
        vehicle_flag = 4;

    });



    car_time = new QTimer(this);
    car_time ->start(100);


    connect(car_time,&QTimer::timeout,[=]()
    {

            appendRowCarData();

    });
}


void vehicle_table::appendRowCarData()
{
    if(trans_start == 1)
    {

    switch(vehicle_flag)
    {
    case 1:
        setRowCount(trans_car_num);//行数

        for(int n = 0; n<trans_car_num; n++)
       {

               setItem(n,0,new QTableWidgetItem(QString("运输车辆%1").arg(n)));
               setItem(n,1,new QTableWidgetItem(QString("%1").arg(trans_effi[n])));
               setItem(n,2,new QTableWidgetItem(QString("%1").arg(trans_velo[n])));
               for(int j = 0;j < gridmap_widget.task_plan1.trans_car_team[n].task_locking.size(); j++)
               {
                   if(gridmap_widget.task_plan1.obstacle_team[gridmap_widget.task_plan1.trans_car_team[n].
                           task_locking[gridmap_widget.task_plan1.trans_car_team[n].task_locking.size()-1]].isfinish != 2)
                   {
                       if(gridmap_widget.task_plan1.obstacle_team[gridmap_widget.task_plan1.trans_car_team[n].task_locking[j]].isfinish != 2)
                       {
                             setItem(n,3,new QTableWidgetItem(QString("%1").arg(gridmap_widget.task_plan1.trans_car_team[n].task_locking[j])));
                             break;
                       }
                   }
                   else
                   {
                       setItem(n,3,new QTableWidgetItem(QString("无任务")));
                       break;
                   }

               }
               if(gridmap_widget.task_plan1.trans_car_team[n].disappear)
               {
                   setItem(n,4,new QTableWidgetItem(QString("是")));
               }
               else
               {
                   setItem(n,4,new QTableWidgetItem(QString("否")));
               }





       }



        break;
   case 2:
        setRowCount(clear_car_num);//行数

        for(int n = 0; n<clear_car_num; n++)
       {
           setItem(n,0,new QTableWidgetItem(QString("清障车辆%1").arg(n)));
           setItem(n,1,new QTableWidgetItem(QString("%1").arg(clear_effi[n])));
           setItem(n,2,new QTableWidgetItem(QString("%1").arg(clear_velo[n])));
           for(int j = 0;j < gridmap_widget.task_plan1.clear_car_team[n].task_locking.size(); j++)
           {
               if(gridmap_widget.task_plan1.stone_team[gridmap_widget.task_plan1.clear_car_team[n].
                       task_locking[gridmap_widget.task_plan1.clear_car_team[n].task_locking.size()-1]].isfinish != 2)
               {
                   if(gridmap_widget.task_plan1.stone_team[gridmap_widget.task_plan1.clear_car_team[n].task_locking[j]].isfinish != 2)
                   {
                         setItem(n,3,new QTableWidgetItem(QString("%1").arg(gridmap_widget.task_plan1.clear_car_team[n].task_locking[j])));
                         break;
                   }
               }
               else
               {
                   setItem(n,3,new QTableWidgetItem(QString("无任务")));
                   break;

               }

           }
           if(gridmap_widget.task_plan1.clear_car_team[n].disappear)
           {
               setItem(n,4,new QTableWidgetItem(QString("是")));
           }
           else
           {
               setItem(n,4,new QTableWidgetItem(QString("否")));
           }


       }


        break;
   case 3:
        setRowCount(bomb_car_num);//行数

        for(int n = 0; n<bomb_car_num; n++)
       {
           setItem(n,0,new QTableWidgetItem(QString("排弹车辆%1").arg(n)));
           setItem(n,1,new QTableWidgetItem(QString("%1").arg(bomb_effi[n])));
           setItem(n,2,new QTableWidgetItem(QString("%1").arg(bomb_velo[n])));
           for(int j = 0;j < gridmap_widget.task_plan1.bomb_car_team[n].task_locking.size(); j++)
           {
               if(gridmap_widget.task_plan1.bomb_team[gridmap_widget.task_plan1.bomb_car_team[n].
                       task_locking[gridmap_widget.task_plan1.bomb_car_team[n].task_locking.size()-1]].isfinish != 2)
               {
                   if(gridmap_widget.task_plan1.bomb_team[gridmap_widget.task_plan1.bomb_car_team[n].task_locking[j]].isfinish != 2)
                   {
                         setItem(n,3,new QTableWidgetItem(QString("%1").arg(gridmap_widget.task_plan1.bomb_car_team[n].task_locking[j])));
                         break;
                   }
               }
               else
               {
                   setItem(n,3,new QTableWidgetItem(QString("无任务")));
                   break;
               }

           }

           if(gridmap_widget.task_plan1.bomb_car_team[n].disappear)
           {
               setItem(n,4,new QTableWidgetItem(QString("是")));
           }
           else
           {
               setItem(n,4,new QTableWidgetItem(QString("否")));
           }


       }
       break;


    case 4:
         setRowCount(repair_car_num);//行数

         for(int n = 0; n<repair_car_num; n++)
        {
            setItem(n,0,new QTableWidgetItem(QString("运输车辆%1").arg(n)));
            setItem(n,1,new QTableWidgetItem(QString("%1").arg(repair_effi[n])));
            setItem(n,2,new QTableWidgetItem(QString("%1").arg(repair_velo[n])));
            if(repair_to_home[n] == 0)
            {
                for(int j = 0;j < gridmap_widget.task_plan1.repair_car_team[n].task_locking.size(); j++)
                {
                    if(gridmap_widget.task_plan1.obstacle_team[gridmap_widget.task_plan1.repair_car_team[n].
                            task_locking[gridmap_widget.task_plan1.repair_car_team[n].task_locking.size()-1]].isfinish2 != 2)
                    {
                        if(gridmap_widget.task_plan1.obstacle_team[gridmap_widget.task_plan1.repair_car_team[n].task_locking[j]].isfinish2 != 2)
                        {
                              setItem(n,3,new QTableWidgetItem(QString("抢修任务点%1").arg(gridmap_widget.task_plan1.repair_car_team[n].task_locking[j])));
                              break;
                        }
                    }
                    else
                    {
                        setItem(n,3,new QTableWidgetItem(QString("无任务")));
                        break;
                    }

                }
            }
            else
            {
                for(int j = 0;j < gridmap_widget.task_plan1.repair_car_team[n].task_locking2.size(); j++)
                {
                    if(gridmap_widget.task_plan1.stone_team[gridmap_widget.task_plan1.repair_car_team[n].
                            task_locking2[gridmap_widget.task_plan1.repair_car_team[n].task_locking2.size()-1]].isfinish2 != 2)
                    {
                        if(gridmap_widget.task_plan1.stone_team[gridmap_widget.task_plan1.repair_car_team[n].task_locking2[j]].isfinish2 != 2)
                        {
                              setItem(n,3,new QTableWidgetItem(QString("清障任务点%1").arg(gridmap_widget.task_plan1.repair_car_team[n].task_locking[j])));
                              break;
                        }
                    }
                    else
                    {
                        setItem(n,3,new QTableWidgetItem(QString("无任务")));
                        break;
                    }

                }
            }


            if(gridmap_widget.task_plan1.repair_car_team[n].disappear)
            {
                setItem(n,4,new QTableWidgetItem(QString("是")));
            }
            else
            {
                setItem(n,4,new QTableWidgetItem(QString("否")));
            }


        }
        break;

    }


    }


}

