#-------------------------------------------------
#
# Project created by QtCreator 2020-01-14T11:44:05
#
#-------------------------------------------------
include(../../QMapControl.pri)
QT+=network
QT+=gui
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): cache()
DEPENDPATH += src
MOC_DIR = tmp
OBJECTS_DIR = obj
DESTDIR = ../bin

TARGET = untitled1
TEMPLATE = app


DEFINES += QT_DEPRECATED_WARNINGS




SOURCES += \
        main.cpp \
        mainwindow.cpp \
    mapviewer.cpp \
    linesandpoints.cpp \
    gps.cpp \
    gps_neo.cpp \
    gps_simulation.cpp \
    schedulerwidget.cpp \
    copter.cpp \
    gridmap.cpp \
    astar.cpp \
    obstacle.cpp \
    trans_car.cpp \
    repair_car.cpp \
    bomb_car.cpp \
    clear_car.cpp \
    bomb.cpp \
    stone.cpp \
    task_table.cpp \
    ga_path.cpp \
    task_plan.cpp \
    vehicle_table.cpp

HEADERS += \
        mainwindow.h \
    mapviewer.h \
    linesandpoints.h \
    gps.h \
    gps_neo.h \
    gps_simulation.h \
    schedulerwidget.h \
    copter.h \
    gridmap.h \
    astar.h \
    obstacle.h \
    trans_car.h \
    repair_car.h \
    bomb_car.h \
    clear_car.h \
    bomb.h \
    stone.h \
    task_table.h \
    ga_path.h \
    task_plan.h \
    vehicle_table.h

FORMS += \
        mainwindow.ui

RESOURCES += \
    resources.qrc
