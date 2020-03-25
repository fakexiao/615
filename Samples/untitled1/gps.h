#ifndef GPS_H
#define GPS_H

#include <QPushButton>
#include <QLabel>
#include <mapcontrol.h>
#include <point.h>
#include "gps_neo.h"
#include "gps_simulation.h"
#include "circlepoint.h"
#include "QTimer"
#include "copter.h"

using namespace qmapcontrol;
class GPS: public QWidget
{
    Q_OBJECT
    public:
    GPS(QWidget *parent = 0);

            ~GPS();

    private:
            QPushButton* followgps;
            QPushButton* simulategps;
            QLabel* gpsposition;
            MapControl* mc;
            GPS_Simulation* gpsSim;
            CirclePoint* gpsDot;

//            int gridW;  //一个格子的宽度
//            int gridH;  //一个格子的高度
//            int startX; //棋盘起点x坐标
//            int startY; //棋盘起点y坐标

//            int m_XPtInterval = 0;
//            int m_YPtInterval = 0;
//            QPoint m_OldPos;
//            bool m_Pressed = false;

//            double factor;

//            QTimer m_timer;

//            copter copter1;

    public slots:
            void updatePosition(float time, QPointF coordinate);
            void resizeEvent(QResizeEvent *qEvent);
            void simulategps_checked();
    protected:
//            void paintEvent(QPaintEvent *);
//            void wheelEvent(QWheelEvent *event);
//            void mousePressEvent(QMouseEvent *event);
//            void mouseMoveEvent(QMouseEvent *event);
//            void mouseReleaseEvent(QMouseEvent *event);

//            void updataposition();
//            void begin_run();
};

#endif
