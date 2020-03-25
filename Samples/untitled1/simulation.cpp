#include "simulation.h"

simulation::simulation(QWidget *parent) : QWidget(parent)
{
    factor = 1.0;

    m_timer.setInterval(100);
    begin_run();
}

void simulation::paintEvent(QPaintEvent *)
{
    gridW = width()/82*factor;  //窗口宽度分10份
    gridH = height()/82*factor; //窗口高度分10份

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
    for(int i = 0; i <= 80; i++)
    {
        //横线
        p.drawLine(startX, startY+i*gridH, startX+80*gridW, startY+i*gridH);

        //竖线
        p.drawLine(startX+i*gridW, startY, startX+i*gridW, startY+80*gridH);
    }

    //画飞机

        p.drawPixmap( startX+copter1.m_X*gridW, startY+copter1.m_Y*gridH,
                        gridW, gridH,
                     copter1.pic_transcar
                     );

}

void simulation::updataposition()
{

if (copter1.down)
{
     copter1.m_Y=copter1.m_Y+1;
     copter1.m_X=copter1.m_X;
     if (copter1.m_Y>=79)
     {
         copter1.down=0;
         copter1.up=1;
        copter1.m_Y=copter1.m_Y;
        copter1.m_X=copter1.m_X+1;
     }
}

   else if (copter1.up)
    {

    copter1.m_Y=copter1.m_Y-1;
    copter1.m_X=copter1.m_X;
    if (copter1.m_Y<=0)
    {
        copter1.down=1;
        copter1.up=0;
       copter1.m_Y=copter1.m_Y;
       copter1.m_X=copter1.m_X+1;
    }

   }


}



void simulation::begin_run()
{
    m_timer.start();
    connect(&m_timer,&QTimer::timeout,[=]()
    {

        updataposition();
        update();

    });
}

void simulation::wheelEvent(QWheelEvent *event)
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


void simulation::mousePressEvent(QMouseEvent *event)
{
    m_OldPos = event->pos();
    m_Pressed = true;
}

void simulation::mouseMoveEvent(QMouseEvent *event)
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

void simulation::mouseReleaseEvent(QMouseEvent *event)
{
    m_Pressed = false;
    this->setCursor(Qt::ArrowCursor);
}


