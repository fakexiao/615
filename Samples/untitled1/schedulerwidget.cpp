#include "schedulerwidget.h"

schedulerwidget::schedulerwidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle(tr("Scheduler Mode"));
    this->setFixedSize(900,500);//设置位置和大小
    this->setWindowOpacity(1);//设置透明度

    Task_Box = new QComboBox(this);
    Task_Box ->setFixedSize(295,45);
    Task_Box ->setStyleSheet("color: rgb(0,255,255)");
    Task_Box ->addItem("任务1");
    Task_Box ->addItem("任务2");
    Task_Box ->addItem("任务3");

    Task_Box1 = new QComboBox(this);
    Task_Box1 ->setFixedSize(295,45);
    Task_Box1 ->setStyleSheet("color: rgb(0,255,255)");
    Task_Box1 ->addItem("任务1");
    Task_Box1 ->addItem("任务2");
    Task_Box1 ->addItem("任务3");

    Task_Box2 = new QComboBox(this);
    Task_Box2 ->setFixedSize(295,45);
    Task_Box2 ->setStyleSheet("color: rgb(0,255,255)");
    Task_Box2 ->addItem("任务1");
    Task_Box2 ->addItem("任务2");
    Task_Box2 ->addItem("任务3");

    Task_Box3 = new QComboBox(this);
    Task_Box3 ->setFixedSize(295,45);
    Task_Box3 ->setStyleSheet("color: rgb(0,255,255)");
    Task_Box3 ->addItem("任务1");
    Task_Box3 ->addItem("任务2");
    Task_Box3 ->addItem("任务3");

    Task_Box4 = new QComboBox(this);
    Task_Box4 ->setFixedSize(295,45);
    Task_Box4 ->setStyleSheet("color: rgb(0,255,255)");
    Task_Box4 ->addItem("任务1");
    Task_Box4 ->addItem("任务2");
    Task_Box4 ->addItem("任务3");

    Task_Box5 = new QComboBox(this);
    Task_Box5 ->setFixedSize(295,45);
    Task_Box5 ->setStyleSheet("color: rgb(0,255,255)");
    Task_Box5 ->addItem("任务1");
    Task_Box5 ->addItem("任务2");
    Task_Box5 ->addItem("任务3");

    Task_Box6 = new QComboBox(this);
    Task_Box6 ->setFixedSize(295,45);
    Task_Box6 ->setStyleSheet("color: rgb(0,255,255)");
    Task_Box6 ->addItem("任务1");
    Task_Box6 ->addItem("任务2");
    Task_Box6 ->addItem("任务3");

    Task_Box7 = new QComboBox(this);
    Task_Box7 ->setFixedSize(295,45);
    Task_Box7 ->setStyleSheet("color: rgb(0,255,255)");
    Task_Box7 ->addItem("任务1");
    Task_Box7 ->addItem("任务2");
    Task_Box7 ->addItem("任务3");

    Task_Box8 = new QComboBox(this);
    Task_Box8 ->setFixedSize(295,45);
    Task_Box8 ->setStyleSheet("color: rgb(0,255,255)");
    Task_Box8 ->addItem("任务1");
    Task_Box8 ->addItem("任务2");
    Task_Box8 ->addItem("任务3");

    ManageTable = new QTableWidget(this);
    ManageTable ->setColumnCount(3);//列数
    ManageTable ->setRowCount(9);//行数
    ManageTable->resize(900, 500);
    ManageTable ->horizontalHeader()->setStyleSheet("QHeaderView::section{background:#444444;}");//行头背景

    ManageTable->verticalHeader()->hide();
    //ManualTable->horizontalHeader()->setStretchLastSection(true);  //设置拉伸最后一列
    ManageTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);  //表头的文字居中
    ManageTable->setStyleSheet(QString( "QTableWidget QHeaderView::section{background:#2a9ee4;font-weight:bold;}"));

    ManageTable->horizontalHeader()->setSectionResizeMode (QHeaderView::Stretch);

    // ManualTable->setEditTriggers(QAbstractItemView::DoubleClicked); //设置编辑

    QStringList manageheader;
    manageheader<<tr("装备种类")<<tr("装备状态")<<tr("任务分配");
    ManageTable->setHorizontalHeaderLabels(manageheader);

    ManageTable ->verticalHeader()->setDefaultSectionSize(50); //设置行高
    ManageTable ->setStyleSheet("QTableView::Item{background-color:#444444}");
    ManageTable ->setItem(0,0,new QTableWidgetItem("运输车辆A"));
    ManageTable ->item(0,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ManageTable ->setItem(1,0,new QTableWidgetItem("保障车辆B"));
    ManageTable ->item(1,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ManageTable ->setItem(2,0,new QTableWidgetItem("排爆车辆C"));
    ManageTable ->item(2,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ManageTable ->setItem(3,0,new QTableWidgetItem("保障车辆A"));
    ManageTable ->item(3,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ManageTable ->setItem(4,0,new QTableWidgetItem("保障车辆B"));
    ManageTable ->item(4,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ManageTable ->setItem(5,0,new QTableWidgetItem("保障车辆C"));
    ManageTable ->item(5,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ManageTable ->setItem(6,0,new QTableWidgetItem("排爆车辆A"));
    ManageTable ->item(6,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ManageTable ->setItem(7,0,new QTableWidgetItem("排爆车辆B"));
    ManageTable ->item(7,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ManageTable ->setItem(8,0,new QTableWidgetItem("排爆车辆C"));
    ManageTable ->item(8,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ManageTable ->setCellWidget(0,2,Task_Box);
    ManageTable ->setCellWidget(1,2,Task_Box1);
    ManageTable ->setCellWidget(2,2,Task_Box2);
    ManageTable ->setCellWidget(3,2,Task_Box3);
    ManageTable ->setCellWidget(4,2,Task_Box4);
    ManageTable ->setCellWidget(5,2,Task_Box5);
    ManageTable ->setCellWidget(6,2,Task_Box6);
    ManageTable ->setCellWidget(7,2,Task_Box7);
    ManageTable ->setCellWidget(8,2,Task_Box8);

}
