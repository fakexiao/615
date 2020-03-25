#ifndef GRIDMAP_H
#define GRIDMAP_H


#include <QPushButton>
#include <QLabel>
#include <QMouseEvent>
#include <point.h>
#include "QTimer"
#include "copter.h"
#include "obstacle.h"
#include "trans_car.h"
#include "bomb.h"
#include "bomb_car.h"
#include "stone.h"
#include "clear_car.h"
#include "repair_car.h"
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QToolButton>
#include "task_plan.h"


class gridmap: public QWidget
{
    Q_OBJECT
    public:
    explicit gridmap(QWidget *parent = nullptr);
    task_plan task_plan1;

    private:
            int gridW;  //一个格子的宽度
            int gridH;  //一个格子的高度
            int startX; //棋盘起点x坐标
            int startY; //棋盘起点y坐标

            bool m_obs = false;







            int m_XPtInterval = 0;
            int m_YPtInterval = 0;

            QPoint m_OldPos;
            bool m_Pressed = false;

            double factor;

            QTimer *m_timer;
            QTimer *e_timer;
            QTimer *h_timer;
            trans_car trans_car1;
            trans_car trans_car_team1[10];
            copter copter1;
            obstacle obstacle1;
            stone stone1;
            bomb bomb1;


            void createMaze();

    public slots:


    protected:
            void paintEvent(QPaintEvent *);
            void wheelEvent(QWheelEvent *event);
            void mousePressEvent(QMouseEvent *event);
            void mouseMoveEvent(QMouseEvent *event);
            void mouseReleaseEvent(QMouseEvent *event);

            void updataposition();
            void begin_run();

            void Start_task();
            void Stop_task();
            void Over_task();
            void Emr_return_task();
            void Emergency_return();
            void Emergency_clear_return();
            void Emergency_bomb_return();
            void Emergency_repair_return();
            void Emergency_copter_return();

};
            void sleep(unsigned int msec);
#endif
