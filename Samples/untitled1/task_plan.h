#ifndef TASK_PLAN_H
#define TASK_PLAN_H

#include "trans_car.h"
#include "obstacle.h"
#include "clear_car.h"
#include "repair_car.h"
#include "stone.h"
#include "bomb_car.h"
#include "bomb.h"
#include  "copter.h"

class task_plan
{
public:
    task_plan();
    trans_car_plan();
    clear_car_plan();
    bomb_car_plan();
    repair_car_plan();
    repair_car_plan2();
    trans_car trans_car_team[20];
    obstacle obstacle_team[20];
    clear_car clear_car_team[20];
    repair_car repair_car_team[20];
    stone stone_team[20];
    bomb_car bomb_car_team[20];
    bomb bomb_team[20];
    copter copter_team[20];

private:
    int t_task_average;
    int time_limit_up;
    int time_limit_down;


};
void SumToM(vector<int> value , int N, int M, int *array, int &sum, int& num);
int time_plus(int a,int b);
#endif // TASK_PLAN_H
