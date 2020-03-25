#include "gps.h"

/*!
 * \example gps.cpp
 * This sample application uses GPS data from the gllin service, which you have to start manually before using this application.
 * The file /tmp/nmeaNP is read in for the posiitons.
 *
 * The application receives positions from the GPS_Neo class and writes it into a label.
 * You can toggle a button to set the view to the received coordinate.
 *
 * You can find this example here: MapAPI/Samples/GPS
 * \image html sample_gps.png "screenshot"
 * @see http://3rdparty.downloads.openmoko.org
 */

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
GPS::GPS(QWidget *parent)
    : QWidget(parent)
{
    // create MapControl
    mc = new MapControl(QSize(480,640));
// 	ImageManager::instance()->setProxy("www-cache", 8080);
    mc->showUAV(true);


    // create MapAdapter to get maps from
    TileMapAdapter* mapadapter = new TileMapAdapter("tile.openstreetmap.org", "/%1/%2/%3.png", 256, 0, 17);

    // create a layer with the mapadapter and type MapLayer
    Layer* l = new Layer("Custom Layer", mapadapter, Layer::MapLayer);

    //current GPS Location
    gpsDot = new CirclePoint(0,0, "GPS", CirclePoint::Middle, new QPen( Qt::darkBlue ));
    l->addGeometry( gpsDot );

    // add Layer to the MapControl
    mc->addLayer(l);

    // display the MapControl in the application
    QHBoxLayout* layout = new QHBoxLayout;
    //layout->addWidget(mc);
    setLayout(layout);

    // create buttons as controls for zoom
    QPushButton* zoomin = new QPushButton("+");
    QPushButton* zoomout = new QPushButton("-");

    followgps = new QPushButton("Follow");
    followgps->setCheckable(true);
    simulategps = new QPushButton("Simulate");
    simulategps->setCheckable(true);
    gpsposition = new QLabel();
    zoomin->setMaximumWidth(50);
    zoomout->setMaximumWidth(50);
    followgps->setMaximumWidth(50);
    simulategps->setMaximumWidth(50);
    gpsposition->setFont(QFont("Arial", 10));

    connect(zoomin, SIGNAL(clicked(bool)),
              mc, SLOT(zoomIn()));
    connect(zoomout, SIGNAL(clicked(bool)),
              mc, SLOT(zoomOut()));

    connect(simulategps, SIGNAL(clicked(bool)),
              this, SLOT(simulategps_checked()));

    // add zoom buttons to the layout of the MapControl
    QVBoxLayout* innerlayout = new QVBoxLayout;
    innerlayout->addWidget(zoomin);
    innerlayout->addWidget(zoomout);
    innerlayout->addWidget(followgps);
    innerlayout->addWidget(simulategps);
    innerlayout->addWidget(gpsposition);
    mc->setLayout(innerlayout);

    GPS_Neo* gm = new GPS_Neo();
    connect(gm, SIGNAL(new_position(float, QPointF)),
              this, SLOT(updatePosition(float, QPointF)));

    gpsSim = new GPS_Simulation(this);
    connect(gpsSim, SIGNAL(newPosition(float,QPointF)),
                        this, SLOT(updatePosition(float, QPointF)));

    mc->setView(QPointF(0, 0));

    gm->start();

//    factor = 1.0;

//    m_timer.setInterval(100);
//    begin_run();
}
//void GPS::paintEvent(QPaintEvent *)
//{
//    QPainter p(mc);
//    p.drawPixmap(0,0,100,100,QPixmap(":/new/prefix1/img/qiangxiu.png"));
//}

GPS::~GPS()
{
}

void GPS::updatePosition(float time, QPointF coordinate)
{
    gpsposition->setText(QString::number(time) + " / " + QString::number(coordinate.x()) + " / " + QString::number(coordinate.y()));
    if (followgps->isChecked())
    {
        mc->setView(coordinate);
    }

    //update the gps dot location on map
    gpsDot->setCoordinate(coordinate);
}

void GPS::resizeEvent(QResizeEvent *qEvent)
{
    Q_UNUSED( qEvent );
    if (mc)
    {
        mc->resize(size());
    }
}

void GPS::simulategps_checked()
{
    if ( simulategps->isChecked() )
    {
        gpsSim->start();
    }
    else
    {
        gpsSim->stop();
    }
}

//void GPS::paintEvent(QPaintEvent *)
//{
//    gridW = width()/82*factor;  //窗口宽度分10份
//    gridH = height()/82*factor; //窗口高度分10份

//    //棋盘起点坐标
//    startX = gridW;
//    startY = gridH;

//    QPainter p(this); //创建画家，指定窗口为绘图设备

//    p.translate(startX + m_XPtInterval, startY + m_YPtInterval);



//    //设置画笔
//    QPen pen;
//    pen.setWidth(2); //线宽
//    p.setPen(pen);  //将画笔交给画家

//    //取中间8份画棋盘
//    for(int i = 0; i <= 80; i++)
//    {
//        //横线
//        p.drawLine(startX, startY+i*gridH, startX+80*gridW, startY+i*gridH);

//        //竖线
//        p.drawLine(startX+i*gridW, startY, startX+i*gridW, startY+80*gridH);
//    }

//    //画飞机

//        p.drawPixmap( startX+copter1.m_X*gridW, startY+copter1.m_Y*gridH,
//                        gridW, gridH,
//                     copter1.pic_transcar
//                     );

//}

//void GPS::updataposition()
//{

//if (copter1.down)
//{
//     copter1.m_Y=copter1.m_Y+1;
//     copter1.m_X=copter1.m_X;
//     if (copter1.m_Y>=79)
//     {
//         copter1.down=0;
//         copter1.up=1;
//        copter1.m_Y=copter1.m_Y;
//        copter1.m_X=copter1.m_X+1;
//     }
//}

//   else if (copter1.up)
//    {

//    copter1.m_Y=copter1.m_Y-1;
//    copter1.m_X=copter1.m_X;
//    if (copter1.m_Y<=0)
//    {
//        copter1.down=1;
//        copter1.up=0;
//       copter1.m_Y=copter1.m_Y;
//       copter1.m_X=copter1.m_X+1;
//    }

//   }


//}



//void GPS::begin_run()
//{
//    m_timer.start();
//    connect(&m_timer,&QTimer::timeout,[=]()
//    {

//        updataposition();
//        update();

//    });
//}

//void GPS::wheelEvent(QWheelEvent *event)
//{
//    double numDegrees = event->delta() / 8.0;
//    double numSteps = numDegrees / 15.0;
//    factor *= pow(1.1, numSteps);
//    if (factor < 0.07)
//        factor = 0.07;
//    if(factor > 50)
//        factor = 50;

//    qDebug() << factor << numDegrees << numSteps << event->delta();
//    update();

//}


//void GPS::mousePressEvent(QMouseEvent *event)
//{
//    m_OldPos = event->pos();
//    m_Pressed = true;
//}

//void GPS::mouseMoveEvent(QMouseEvent *event)
//{
//    if (!m_Pressed)
//        return QWidget::mouseMoveEvent(event);

//    this->setCursor(Qt::SizeAllCursor);
//    QPoint pos = event->pos();
//    int xPtInterval = pos.x() - m_OldPos.x();
//    int yPtInterval = pos.y() - m_OldPos.y();

//    m_XPtInterval += xPtInterval;
//    m_YPtInterval += yPtInterval;

//    m_OldPos = pos;
//    this->update();
//}

//void GPS::mouseReleaseEvent(QMouseEvent *event)
//{
//    m_Pressed = false;
//    this->setCursor(Qt::ArrowCursor);
//}



