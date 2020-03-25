#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDialog>
#include <QMainWindow>
#include "schedulerwidget.h"
//#include "gridmap.h"

#include <QTableWidget>
#include <QStyledItemDelegate>
#include "QTimer"
#include "copter.h"
#include "astar.h"
#include "trans_car.h"
#include "task_table.h"
#include "vehicle_table.h"

#define ROW 80
#define COL 60

#define ROWCOUNTPERPAGE 15
#define ROWHEIGHT 60//行高




namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();





private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void Scheduler_show();

    void Gridmap_show();

    void Task_table_show();

    void vehicle_table_show();

    void on_pushButton_12_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_27_clicked();

private:
    Ui::MainWindow *ui;

    schedulerwidget Scheduler_widget;
//    gridmap gridmap_widget;
    Task_table Task_table_widget;
    vehicle_table vehicle_table_widget;





};



#endif // MAINWINDOW_H
