#ifndef TASK_TABLE_H
#define TASK_TABLE_H

#include <QTableWidget>
#include <QStyledItemDelegate>
#include <QTimer>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QToolButton>

#define ROWCOUNTPERPAGE 15
#define ROWHEIGHT 60//行高

class Task_table : public QTableWidget
{
    Q_OBJECT
public:
    explicit Task_table(QWidget *parent = 0);
    ~Task_table();

    /**
     * @brief appendRowData            添加一行数据到最后一行
     */
    void appendRowData();

signals:


protected:



private:

    QTimer *P_time;

};




#endif
