#pragma execution_character_set("utf-8")
#include "task_table.h"
#include <QHeaderView>
#include <QDebug>
#include <QTextOption>
#include <QPainter>
#include <QPushButton>
#include <QHBoxLayout>

#include <QScrollBar>
#include <QHeaderView>
#include <QDebug>

extern int obs_num;
extern int obstacle_num;
extern int bomb_see_num;
extern int stone_see_num;
extern int obs_x[20];
extern int obs_y[20];
extern int stone_x[20];
extern int stone_y[20];
extern int bomb_x[20];
extern int bomb_y[20];
extern int obs_count[20];
extern int bomb_count[20];
extern int stone_count[20];
extern int obs_comp[20];
extern int stone_comp[20];
extern int bomb_comp[20];
extern int obs_table[20];
extern int stone_table[20];
extern int bomb_table[20];

int task_flag;

Task_table::Task_table(QWidget *parent)
    : QTableWidget(parent)
{
    setWindowTitle(tr("任务点信息"));
    this->setFixedSize(800,600);//设置位置和大小
    this->setWindowOpacity(1);//设置透明度


        setColumnCount(3);//列数

        horizontalHeader()->setStyleSheet("QHeaderView::section{background:#444444;color:white;font:bold 10pt '楷体' ;}");//行头背景

        verticalHeader()->hide();

        horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);  //表头的文字居中
        setStyleSheet(QString( "QTableWidget QHeaderView::section{background:#2a9ee4;font-weight:bold;}"));

        horizontalHeader()->setSectionResizeMode (QHeaderView::Stretch);



        QStringList header1;
        header1<<tr("任务点")<<tr("坐标")<<tr("复杂度");
        setHorizontalHeaderLabels(header1);


        horizontalHeader()->setMinimumHeight(50);
        verticalHeader()->setDefaultSectionSize(50); //设置行高
        setStyleSheet("QTableView::Item{background-color:#444444}");


        P_time = new QTimer(this);
        P_time ->start(100);

        connect(P_time,&QTimer::timeout,[=]()
        {

             appendRowData();

        });


        QToolButton *toolButton1 = new QToolButton(this); //新建toolButton
        toolButton1->setText("任务类型"); //设置内容
        toolButton1->setPopupMode(QToolButton::InstantPopup); //设置模式 必须
        toolButton1->setFixedSize(268,51);


        QMenu * p = new QMenu(this); //创建菜单
        QAction *p1 = p->addAction("排弹任务");
        QAction *p2 = p->addAction("清障任务");
        QAction *p3 = p->addAction("抢修任务");
        toolButton1->setMenu(p); //将菜单添加到toolButton中

        toolButton1->setStyleSheet("\
            QToolButton::menu-indicator{\
            image: none;\
        }");
        connect(p1, &QAction::triggered,
                [=]()
        {
            task_flag = 1;

        });

        connect(p2, &QAction::triggered,
                [=]()
        {
            task_flag = 2;

        });

        connect(p3, &QAction::triggered,
                [=]()
        {
            task_flag = 3;

        });


}

Task_table::~Task_table()
{

}

void Task_table::appendRowData()
{


    setRowCount(obs_num);





switch(task_flag)
{
case 1:
    for(int n = 0; n<bomb_see_num; n++)
    {
        setItem(n,0,new QTableWidgetItem(QString("排弹任务%1").arg(n)));
        setItem(n,1,new QTableWidgetItem(QString("[%1,%2]").arg(bomb_y[bomb_table[n]]).arg(bomb_x[bomb_table[n]])));
        setItem(n,2,new QTableWidgetItem(QString("%1").arg(bomb_comp[bomb_table[n]])));
    }
     break;
case 2:
    for(int n = 0; n<stone_see_num; n++)
    {
        setItem(n,0,new QTableWidgetItem(QString("清障任务%1").arg(n)));
        setItem(n,1,new QTableWidgetItem(QString("[%1,%2]").arg(stone_y[stone_table[n]]).arg(stone_x[stone_table[n]])));
        setItem(n,2,new QTableWidgetItem(QString("%1").arg(stone_comp[stone_table[n]])));

    }
     break;
case 3:
    for(int n = 0; n<obstacle_num; n++)
   {
       setItem(n,0,new QTableWidgetItem(QString("抢修任务%1").arg(n)));
       setItem(n,1,new QTableWidgetItem(QString("[%1,%2]").arg(obs_y[obs_table[n]]).arg(obs_x[obs_table[n]])));
       setItem(n,2,new QTableWidgetItem(QString("%1").arg(obs_comp[obs_table[n]])));

   }
    break;


}


}







