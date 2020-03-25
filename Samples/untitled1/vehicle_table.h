#ifndef VEHICLE_TABLE_H
#define VEHICLE_TABLE_H

#include <QTableWidget>
#include <QStyledItemDelegate>
#include <QTimer>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QToolButton>
#include "gridmap.h"
#include <QComboBox>




class vehicle_table : public QTableWidget
{
    Q_OBJECT
public:
    explicit vehicle_table(QWidget *parent = 0);
        gridmap gridmap_widget;
    //gridmap gridmap_plan;
    void appendRowCarData();
    QTimer *car_time;
    QComboBox *Task_Box;


};

#endif
