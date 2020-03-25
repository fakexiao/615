#ifndef SCHEDULERWIDGET_H
#define SCHEDULERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QTableWidget>
#include <QComboBox>
#include <QHeaderView>
#include <QVector>
#include <QSpacerItem>
#include <QtAlgorithms>
#include <QTableWidgetItem>
#include <QTabWidget>

class schedulerwidget : public QWidget
{
    Q_OBJECT
public:
    explicit schedulerwidget(QWidget *parent = nullptr);
    QTableWidget *ManageTable;
    QComboBox *Task_Box;
    QComboBox *Task_Box1;
    QComboBox *Task_Box2;
    QComboBox *Task_Box3;
    QComboBox *Task_Box4;
    QComboBox *Task_Box5;
    QComboBox *Task_Box6;
    QComboBox *Task_Box7;
    QComboBox *Task_Box8;
};

#endif // SCHEDULERWIDGET_H
