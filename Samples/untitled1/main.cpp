#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("机场排弹抢修的装备联合调度与规划软件");  //修改这句即可，但是字母，汉字乱码
    w.setWindowIcon(QIcon(":/new/prefix1/img/wurenji.png"));
    w.show();

    return a.exec();
}
