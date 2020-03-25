#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QPen>
#include <QTimer>
#include <QTime>
#include <QMessageBox>

#include <QHeaderView>
#include <QDebug>
#include <QTextOption>
#include <QPushButton>
#include <QHBoxLayout>

#include <QScrollBar>
#include <QHeaderView>



int obs_x[20] = {0};
int obs_y[20] = {0};
int stone_x[20] = {0};
int stone_y[20] = {0};
int bomb_x[20] = {0};
int bomb_y[20] = {0};
int trans_num[20] = {0};
int repair_num[20] = {0};
int bomb_num[20] ={0};
int clear_num[20] = {0};
float trans_effi[20] = {0};
float bomb_effi[20] = {0};
float repair_effi[20] = {0};
float clear_effi[20] = {0};
int trans_velo[20] = {0};
int repair_velo[20] = {0};
int bomb_velo[20] = {0};
int clear_velo[20] = {0};
int trans_oil[20] = {0};
int bomb_oil[20] = {0};
int clear_oil[20] = {0};
float trans_effi_sum;
float bomb_effi_sum;
float clear_effi_sum;
float repair_effi_sum;
int obs_num = 0;
int veh_num = 0;
int obs_comp[20] = {0};
int stone_comp[20] = {0};
int bomb_comp[20] = {0};
int trans_car_num;
int bomb_car_num;
int clear_car_num;
int repair_car_num;
int copter_num;
int clearfinish[20] = {0};
int repairfinish[20] = {0};
int bombfinish[20] = {0};
int trans_crash;
int bomb_crash;
int clear_crash;
int repair_crash;
int trans_crash_flag;
int bomb_crash_flag;
int clear_crash_flag;
int repair_crash_flag;

extern int obs_count[20];
extern int stone_count[20];
extern int bomb_count[20];



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui ->setupUi(this);
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background,QColor(72,72,72));
    this->setPalette(palette);



    ui ->pushButton_21 -> setFixedSize(120,40);
    ui ->pushButton_21 -> setStyleSheet("QPushButton{background-color:rgb(72,72,72);color: rgb(150,200,243); border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                 "QPushButton:hover{background-color:rgb(172,172,172); color: black;}"
                                 "QPushButton:pressed{background-color:rgb(85,170,255);border-style: inset;}");
    ui ->pushButton_22 -> setFixedSize(120,40);
    ui ->pushButton_22 -> setStyleSheet("QPushButton{background-color:rgb(72,72,72);color: rgb(150,200,243); border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                 "QPushButton:hover{background-color:rgb(172,172,172); color: black;}"
                                 "QPushButton:pressed{background-color:rgb(85,170,255);border-style: inset;}");
    ui ->pushButton_23 -> setFixedSize(120,40);
    ui ->pushButton_23 -> setStyleSheet("QPushButton{background-color:rgb(72,72,72);color: rgb(150,200,243); border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                 "QPushButton:hover{background-color:rgb(172,172,172); color: black;}"
                                 "QPushButton:pressed{background-color:rgb(85,170,255);border-style: inset;}");
    ui ->pushButton_24 -> setFixedSize(120,40);
    ui ->pushButton_24 -> setStyleSheet("QPushButton{background-color:rgb(72,72,72);color: rgb(150,200,243); border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                 "QPushButton:hover{background-color:rgb(172,172,172); color: black;}"
                                 "QPushButton:pressed{background-color:rgb(85,170,255);border-style: inset;}");
    ui ->pushButton_5 -> setFixedSize(120,40);
    ui ->pushButton_5 -> setStyleSheet("QPushButton{background-color:rgb(72,72,72);color: rgb(150,200,243); border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                 "QPushButton:hover{background-color:rgb(172,172,172); color: black;}"
                                 "QPushButton:pressed{background-color:rgb(85,170,255);border-style: inset;}");

    ui ->pushButton_11 -> setFixedSize(120,40);
    ui ->pushButton_11 ->setStyleSheet("QPushButton{background-color:rgb(72,72,72);color: rgb(150,200,243); border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                 "QPushButton:hover{background-color:rgb(172,172,172); color: black;}"
                                 "QPushButton:pressed{background-color:rgb(85,170,255);border-style: inset;}");
    ui ->pushButton_12 -> setFixedSize(120,40);
    ui ->pushButton_12 ->setStyleSheet("QPushButton{background-color:rgb(72,72,72);color: rgb(150,200,243); border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                 "QPushButton:hover{background-color:rgb(172,172,172); color: black;}"
                                 "QPushButton:pressed{background-color:rgb(85,170,255);border-style: inset;}");
    ui ->pushButton_17 -> setFixedSize(120,40);
    ui ->pushButton_17 ->setStyleSheet("QPushButton{background-color:rgb(72,72,72);color: rgb(150,200,243); border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                 "QPushButton:hover{background-color:rgb(172,172,172); color: black;}"
                                 "QPushButton:pressed{background-color:rgb(85,170,255);border-style: inset;}");
    ui ->pushButton_27 -> setFixedSize(120,40);
    ui ->pushButton_27 ->setStyleSheet("QPushButton{background-color:rgb(72,72,72);color: rgb(150,200,243); border-radius: 10px;  border: 2px groove gray;border-style: outset;}"
                                 "QPushButton:hover{background-color:rgb(172,172,172); color: black;}"
                                 "QPushButton:pressed{background-color:rgb(85,170,255);border-style: inset;}");
    ui ->pushButton_13 ->setIcon(QIcon(":/new/prefix1/img/wurenji.png"));
    ui ->pushButton_13 ->setFlat(true);
    ui ->pushButton_13 ->setIconSize(QSize(75,90));

    ui ->pushButton_14 ->setIcon(QIcon(":/new/prefix1/img/sanjiao.png"));
    ui ->pushButton_14 ->setFlat(true);
    ui ->pushButton_14 ->setIconSize(QSize(75,90));

    ui ->pushButton_15 ->setIcon(QIcon(":/new/prefix1/img/yuan.png"));
    ui ->pushButton_15 ->setFlat(true);
    ui ->pushButton_15 ->setIconSize(QSize(75,90));

    ui ->pushButton_16 ->setIcon(QIcon(":/new/prefix1/img/ling.png"));
    ui ->pushButton_16 ->setFlat(true);
    ui ->pushButton_16 ->setIconSize(QSize(75,90));

    ui ->pushButton_18 ->setIcon(QIcon(":/new/prefix1/img/dankeng.jpg"));
    ui ->pushButton_18 ->setFlat(true);
    ui ->pushButton_18 ->setIconSize(QSize(75,90));

    ui ->pushButton_19 ->setIcon(QIcon(":/new/prefix1/img/stone.jpg"));
    ui ->pushButton_19 ->setFlat(true);
    ui ->pushButton_19 ->setIconSize(QSize(75,90));

    ui ->pushButton_20 ->setIcon(QIcon(":/new/prefix1/img/bomb.jpg"));
    ui ->pushButton_20 ->setFlat(true);
    ui ->pushButton_20 ->setIconSize(QSize(75,110));

    ui ->pushButton_25 ->setIcon(QIcon(":/new/prefix1/img/wujiao.png"));
    ui ->pushButton_25 ->setFlat(true);
    ui ->pushButton_25 ->setIconSize(QSize(75,110));

    ui ->pushButton_26 ->setIcon(QIcon(":/new/prefix1/img/tushifang.jpg"));
    ui ->pushButton_26 ->setFlat(true);
    ui ->pushButton_26 ->setIconSize(QSize(75,110));



}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_pushButton_3_clicked()
{

}

void MainWindow::on_pushButton_4_clicked()
{

}


void MainWindow::on_pushButton_6_clicked()
{

}

void MainWindow::on_pushButton_7_clicked()
{

}

void MainWindow::on_pushButton_8_clicked()
{

}

void MainWindow::on_pushButton_9_clicked()
{

}

void MainWindow::on_pushButton_10_clicked()
{
    Scheduler_show();
}

void MainWindow::Scheduler_show(){

    Scheduler_widget.show();

}
void MainWindow::Gridmap_show(){

    vehicle_table_widget.gridmap_widget.show();

}




void MainWindow::on_pushButton_12_clicked()
{
    if(obs_num < 20)
    {
        if(!ui->lineEdit_28->text().isEmpty()&&!ui->lineEdit_26->text().isEmpty()&&!ui->lineEdit_31->text().isEmpty())
        {
            obs_x[obs_num] = ui->lineEdit_26->text().toInt();
            obs_y[obs_num] = ui->lineEdit_28->text().toInt();
            obs_comp[obs_num] = ui->lineEdit_31->text().toInt();

        }
        if(!ui->lineEdit_24->text().isEmpty()&&!ui->lineEdit_25->text().isEmpty()&&!ui->lineEdit_30->text().isEmpty())
        {
            stone_x[obs_num] = ui->lineEdit_25->text().toInt();
            stone_y[obs_num] = ui->lineEdit_24->text().toInt();
            stone_comp[obs_num] = ui->lineEdit_30->text().toInt();

        }
        else
        {
            clearfinish[obs_num] = 1;
        }
        if(!ui->lineEdit_29->text().isEmpty()&&!ui->lineEdit_27->text().isEmpty()&&!ui->lineEdit_32->text().isEmpty())
        {
            bomb_x[obs_num] = ui->lineEdit_27->text().toInt();
            bomb_y[obs_num] = ui->lineEdit_29->text().toInt();
            bomb_comp[obs_num] = ui->lineEdit_32->text().toInt();

        }
        else
        {
            bombfinish[obs_num] = 1;
        }

        obs_num++;
    }



        update();
        ui->lineEdit_28->clear();
        ui->lineEdit_26->clear();
        ui->lineEdit_24->clear();
        ui->lineEdit_25->clear();
        ui->lineEdit_29->clear();
        ui->lineEdit_27->clear();
        ui->lineEdit_30->clear();
        ui->lineEdit_31->clear();
        ui->lineEdit_32->clear();

}

void MainWindow::on_pushButton_17_clicked()
{
     Task_table_show();
}


void MainWindow::Task_table_show(){

    Task_table_widget.resize(1000,600);
    Task_table_widget.show();

}

void MainWindow::on_pushButton_5_clicked()
{
    vehicle_table_show();
}

void MainWindow::vehicle_table_show(){

    vehicle_table_widget.resize(1000,600);
    vehicle_table_widget.show();

}

void MainWindow::on_pushButton_11_clicked()
{
    if(!ui->lineEdit_39->text().isEmpty())
    {
          copter_num = ui->lineEdit_39->text().toInt();
    }


        if(veh_num < 20)
        {
            if(!ui->lineEdit_35->text().isEmpty()&&
                    !ui->lineEdit_11->text().isEmpty()&&
                    !ui->lineEdit_15->text().isEmpty()
                    )
            {
                trans_num[veh_num] = ui->lineEdit_35->text().toInt();
                for(int i = 0; i < trans_num[veh_num]; i++)
                {
                    trans_effi[trans_car_num + i] = ui->lineEdit_11->text().toFloat();
                    trans_velo[trans_car_num + i] = ui->lineEdit_15->text().toInt();

                    trans_effi_sum += trans_effi[trans_car_num + i];
                }

            }

            if(!ui->lineEdit_40->text().isEmpty()&&
                    !ui->lineEdit_41->text().isEmpty()&&
                    !ui->lineEdit_12->text().isEmpty())
            {
                  repair_num[veh_num] = ui->lineEdit_40->text().toInt();
                  for(int i = 0; i < repair_num[veh_num]; i++)
                  {
                      repair_effi[repair_car_num + i] = ui->lineEdit_11->text().toFloat();
                      repair_velo[repair_car_num + i] = ui->lineEdit_41->text().toInt();

                      repair_effi_sum += repair_effi[repair_car_num + i];

                  }
            }

            if(!ui->lineEdit_33->text().isEmpty()&&
                    !ui->lineEdit_8->text().isEmpty()&&
                    !ui->lineEdit_13->text().isEmpty()
                    )
            {
                bomb_num[veh_num] = ui->lineEdit_33->text().toInt();
                for(int i = 0; i < bomb_num[veh_num]; i++)
                {
                    bomb_effi[bomb_car_num + i] = ui->lineEdit_8->text().toFloat();
                    bomb_velo[bomb_car_num + i] = ui->lineEdit_13->text().toInt();

                    bomb_effi_sum += bomb_effi[bomb_car_num + i];
                }

            }

            if(!ui->lineEdit_34->text().isEmpty()&&
                    !ui->lineEdit_10->text().isEmpty()&&
                    !ui->lineEdit_14->text().isEmpty()
                    )
            {
                clear_num[veh_num] = ui->lineEdit_34->text().toInt();
                for(int i = 0; i < clear_num[veh_num]; i++)
                {
                    clear_effi[clear_car_num + i] = ui->lineEdit_10->text().toFloat();
                    clear_velo[clear_car_num + i] = ui->lineEdit_14->text().toInt();

                    clear_effi_sum += clear_effi[clear_car_num + i];
                }

            }

            trans_car_num += trans_num[veh_num];
            bomb_car_num += bomb_num[veh_num];
            clear_car_num += clear_num[veh_num];
            repair_car_num += repair_num[veh_num];

            veh_num++;
        }


        ui->lineEdit_35->clear();
        ui->lineEdit_39->clear();
        ui->lineEdit_40->clear();
        ui->lineEdit_41->clear();
        ui->lineEdit_33->clear();
        ui->lineEdit_34->clear();
        ui->lineEdit_11->clear();
        ui->lineEdit_12->clear();
        ui->lineEdit_15->clear();

        ui->lineEdit_8->clear();
        ui->lineEdit_13->clear();

        ui->lineEdit_10->clear();
        ui->lineEdit_14->clear();




}



void MainWindow::on_pushButton_21_clicked()
{

    bomb_crash = ui->lineEdit_36->text().toInt();
    bomb_crash_flag = 1;


   stone_x[obs_num] = vehicle_table_widget.gridmap_widget.task_plan1.bomb_car_team[ui->lineEdit_36->text().toInt()].m_X;
   stone_y[obs_num] = vehicle_table_widget.gridmap_widget.task_plan1.bomb_car_team[ui->lineEdit_36->text().toInt()].m_Y;
   stone_comp[obs_num] = 1;
   stone_count[obs_num] = 1;
   bombfinish[obs_num] = 1;
   obs_num++;





}

void MainWindow::on_pushButton_22_clicked()
{
    clear_crash = ui->lineEdit_37->text().toInt();
    clear_crash_flag = 1;


    stone_x[obs_num] = vehicle_table_widget.gridmap_widget.task_plan1.clear_car_team[ui->lineEdit_37->text().toInt()].m_X;
    stone_y[obs_num] = vehicle_table_widget.gridmap_widget.task_plan1.clear_car_team[ui->lineEdit_37->text().toInt()].m_Y;
    stone_comp[obs_num] = 1;
    stone_count[obs_num] = 1;
    bombfinish[obs_num] = 1;
    obs_num++;
}

void MainWindow::on_pushButton_23_clicked()
{
    trans_crash = ui->lineEdit_38->text().toInt();
    trans_crash_flag = 1;


    stone_x[obs_num] = vehicle_table_widget.gridmap_widget.task_plan1.trans_car_team[ui->lineEdit_38->text().toInt()].m_X;
    stone_y[obs_num] = vehicle_table_widget.gridmap_widget.task_plan1.trans_car_team[ui->lineEdit_38->text().toInt()].m_Y;
    stone_comp[obs_num] = 1;
    stone_count[obs_num] = 1;
    bombfinish[obs_num] = 1;
    obs_num++;
}

void MainWindow::on_pushButton_24_clicked()
{
    Gridmap_show();
}



void MainWindow::on_pushButton_27_clicked()
{
    repair_crash = ui->lineEdit_42->text().toInt();
    repair_crash_flag = 1;


    stone_x[obs_num] = vehicle_table_widget.gridmap_widget.task_plan1.repair_car_team[ui->lineEdit_42->text().toInt()].m_X;
    stone_y[obs_num] = vehicle_table_widget.gridmap_widget.task_plan1.repair_car_team[ui->lineEdit_42->text().toInt()].m_Y;
    stone_comp[obs_num] = 1;
    stone_count[obs_num] = 1;
    bombfinish[obs_num] = 1;
    obs_num++;
}
