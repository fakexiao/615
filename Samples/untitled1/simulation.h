#ifndef SIMULATION_H
#define SIMULATION_H

#include <QPushButton>
#include <QLabel>
#include <mapcontrol.h>
#include <point.h>
#include "gps_neo.h"
#include "gps_simulation.h"
#include "circlepoint.h"
#include "QTimer"
#include "copter.h"


class simulation: public QWidget
{
    Q_OBJECT
    public:
    simulation(QWidget *parent = 0);

            ~simulation();

    private:
            int gridW;  //一个格子的宽度
            int gridH;  //一个格子的高度
            int startX; //棋盘起点x坐标
            int startY; //棋盘起点y坐标

            int m_XPtInterval = 0;
            int m_YPtInterval = 0;
            QPoint m_OldPos;
            bool m_Pressed = false;

            double factor;

            QTimer m_timer;

            copter copter1;

    public slots:
            void updatePosition(float time, QPointF coordinate);
            void resizeEvent(QResizeEvent *qEvent);
            void simulategps_checked();
    protected:
            void paintEvent(QPaintEvent *);
            void wheelEvent(QWheelEvent *event);
            void mousePressEvent(QMouseEvent *event);
            void mouseMoveEvent(QMouseEvent *event);
            void mouseReleaseEvent(QMouseEvent *event);

            void updataposition();
            void begin_run();
};

#endif
