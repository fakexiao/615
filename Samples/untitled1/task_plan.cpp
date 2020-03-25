#include "task_plan.h"
#include "stdio.h"
#include "numeric"
#include "ga_path.h"
#include "math.h"
#include "gridmap.h"

extern int trans_car_num;
extern int obstacle_num;
extern int obs_x[20];
extern int obs_y[20];
extern int clear_car_num;
extern int stone_see_num;
extern int repair_car_num;
extern int copter_num;
extern int stone_x[20];
extern int stone_y[20];
extern int bomb_car_num;
extern int bomb_see_num;
extern int bomb_x[20];
extern int bomb_y[20];
extern int stone_comp[20];
extern int stone_table[20];
extern float t_trans_task_average;
extern float time_trans_limit_up;
extern float time_trans_limit_down;
extern float t_clear_task_average;
extern float time_clear_limit_up;
extern float time_clear_limit_down;
extern float t_bomb_task_average;
extern float time_bomb_limit_up;
extern float time_bomb_limit_down;
extern float t_repair_task_average;
extern float time_repair_limit_up;
extern float time_repair_limit_down;
extern float t_repair_task_average2;
extern float time_repair_limit_up2;
extern float time_repair_limit_down2;


task_plan::task_plan()
{


}


task_plan::trans_car_plan()
{
    vector<int>  task_no_temp;//未锁定任务序号
    vector<int>  task_time_temp;//某个车辆对所有未锁定任务的时间数组

    int arr[20]={0};
    int sum=0;
    int num=0;//一对多用
    int arr1[20]={0};
    int sum1=0;
    int num1=0; //多对一用




    for(int j=0;j<obstacle_num;j++)
        obstacle_team[j].type=0;
    for(int j=0;j<trans_car_num;j++)
        trans_car_team[j].task_flag=0;

    /*一对一情况*/
    for(int i=0;i<trans_car_num;i++)
    {
        for(int j=0;j<obstacle_num;j++)
        {
            if((time_trans_limit_down<=trans_car_team[i].task_time[j]
                &&trans_car_team[i].task_time[j]<=time_trans_limit_up)
                    &&obstacle_team[j].type==0
                    &&trans_car_team[i].task_flag==0)//满足时间区间并且任务未锁定
            {
                trans_car_team[i].task_locking.push_back(j);
                trans_car_team[i].task_flag=1;   //车辆锁定
                obstacle_team[j].type=1;//任务锁定
            }
        }
        task_no_temp.clear();
        for(int j=0;j<obstacle_num;j++)
        {
            if(obstacle_team[j].type==0) //任务未锁定
                task_no_temp.push_back(j);//将未锁定的任务序号放入task_time_temp
        }

    }

    /*单车对多任务情况*/

    for(int i=0;i<trans_car_num;i++)
    {
        if( trans_car_team[i].task_flag==0)
        {


            for(int k=0; k<task_no_temp.size();k++)
            {
                task_time_temp.push_back(trans_car_team[i].task_time[task_no_temp[k]]);//给未锁定任务时间数组赋值
            }


            SumToM(task_time_temp,task_time_temp.size(),time_trans_limit_up,arr,sum,num);
            task_time_temp.clear();//使用完毕清零
            if(sum!=0)
            {
                if(time_trans_limit_down<=sum
                        &&sum<=time_trans_limit_up)

                    for (int k=0;k<obstacle_num;k++)//所有任务时间遍历

                    {
                        for(int j=0;j<num;j++)
                            if(trans_car_team[i].task_time[k]==arr[j]&&obstacle_team[k].type==0)//车辆时间序列等于arr中的值，且该任务的类型为0
                            {
                                trans_car_team[i].task_locking.push_back(k);
                                trans_car_team[i].task_flag=1;   //车辆锁定
                                obstacle_team[k].type=1;//任务锁定
                            }
                    }
            }
        }

        task_no_temp.clear();
        for(int j=0;j<obstacle_num;j++)
        {

            if(obstacle_team[j].type==0) //任务未锁定
                task_no_temp.push_back(j);//将未锁定的任务序号放入task_time_temp
        }
    }


    /*多车对单任务的情况*/
    vector<int>  task_temp;//未安排汽车对某个任务所需时间
    vector<int> car_no_temp;//空闲汽车的序号

    int_least32_t t_task_average_temp;
    for(int j=0;j<obstacle_num;j++)//遍历所有空闲任务
    {
        if(obstacle_team[j].type==0)
        {
            car_no_temp.clear();
            task_temp.clear();
            for(int i=0;i<trans_car_num;i++) //遍历所有空闲车辆
                if( trans_car_team[i].task_flag==0)
                {
                    {
                        task_temp.push_back((1/(float)trans_car_team[i].task_time[j])*1000);//对完成时间取倒数*1000保证小数点
                        t_task_average_temp=(1/(float)time_trans_limit_up)*1000;
                        car_no_temp.push_back(i);//未安排的汽车序号

                    }
                }
            SumToM(task_temp,task_temp.size(),t_task_average_temp,arr1,sum1,num1);
            if(sum1!=0)
            {  if(time_trans_limit_down<=(double)(1000/sum1)
                        && (double)(1000/sum1) <=time_trans_limit_up)
                {
                    obstacle_team[j].type=1;//符合区间条件则任务锁定
                    /*找到符合要求的几辆汽车的序号，将他们的锁定，并且确定他们的任务*/


                    for(int k=0;k<task_temp.size();k++)//遍历所有空闲车辆对任务j的时间倒数
                    {
                        for(int z=0;z<num1;z++)//遍历求到的几辆汽车对任务j的时间倒数
                        {  if(trans_car_team[car_no_temp[k]].task_flag==0)
                            {
                                if(task_temp[k]==arr1[z])//如果两者相同
                                {
                                    trans_car_team[car_no_temp[k]].task_flag=1;   //将车辆锁定
                                    trans_car_team[car_no_temp[k]].task_locking.push_back(j);
                                }
                            }
                        }
                    }

                }
            }
        }
    }
    /* 多车对多任务*/

    task_no_temp.clear();//未锁定任务序号
    car_no_temp.clear();//未锁定车辆序号

    for(int i=0;i<trans_car_num;i++) //遍历所有空闲车辆
        if( trans_car_team[i].task_flag==0)
            car_no_temp.push_back(i);//未安排的汽车序号
    for(int j=0;j<obstacle_num;j++)
        if(obstacle_team[j].type==0) //任务未锁定
            task_no_temp.push_back(j);//将未锁定的任务序号放入task_time_temp
    if(task_no_temp.size()>=car_no_temp.size()&&car_no_temp.size()!=0)//剩余的任务较多
    {

        for(int i=0;i<task_no_temp.size();i++)
        {   int num=i%car_no_temp.size();

            trans_car_team[car_no_temp[num]].task_locking.push_back(task_no_temp[i]);//按顺序分摊所有任务到所有车辆
            trans_car_team[car_no_temp[num]].task_flag=1;
            obstacle_team[task_no_temp[i]].type=1;
        }

    }

    if(car_no_temp.size()>task_no_temp.size()&&task_no_temp.size()!=0)//剩余的车辆较多
    {

        for(int i=0;i<car_no_temp.size();i++)
        {
            int num=i%task_no_temp.size();
            trans_car_team[car_no_temp[i]].task_locking.push_back(task_no_temp[num]);//按顺序分摊所有车辆到任务
            trans_car_team[car_no_temp[i]].task_flag=1;
            obstacle_team[task_no_temp[num]].type=1;
        }

    }

}


task_plan::clear_car_plan()
{
    vector<int>  task_no_temp;//未锁定任务序号
    vector<int>  task_time_temp;//某个车辆对所有未锁定任务的时间数组

    int arr[20]={0};
    int sum=0;
    int num=0;//一对多用
    int arr1[20]={0};
    int sum1=0;
    int num1=0; //多对一用

    for(int j=0;j<stone_see_num;j++)
        stone_team[j].type=0;
    for(int j=0;j<clear_car_num;j++)
        clear_car_team[j].task_flag=0;

    /*一对一情况*/
    for(int i=0;i<clear_car_num;i++)
    {
        for(int j=0;j<stone_see_num;j++)
        {
            if((time_clear_limit_down<=clear_car_team[i].task_time[j]
                &&clear_car_team[i].task_time[j]<=time_clear_limit_up)
                    &&stone_team[j].type==0
                    &&clear_car_team[i].task_flag==0)//满足时间区间并且任务未锁定
            {
                clear_car_team[i].task_locking.push_back(j);
                clear_car_team[i].task_flag=1;   //车辆锁定
                stone_team[j].type=1;//任务锁定
            }
        }
        task_no_temp.clear();
        for(int j=0;j<stone_see_num;j++)
        {
            if(stone_team[j].type==0) //任务未锁定
                task_no_temp.push_back(j);//将未锁定的任务序号放入task_time_temp
        }

    }

    /*单车对多任务情况*/

    for(int i=0;i<clear_car_num;i++)
    {
        if( clear_car_team[i].task_flag==0)
        {


            for(int k=0; k<task_no_temp.size();k++)
            {
                task_time_temp.push_back(clear_car_team[i].task_time[task_no_temp[k]]);//给未锁定任务时间数组赋值
            }


            SumToM(task_time_temp,task_time_temp.size(),time_clear_limit_up,arr,sum,num);
            task_time_temp.clear();//使用完毕清零
            if(sum!=0)
            {
                if(time_clear_limit_down<=sum
                        &&sum<=time_clear_limit_up)

                    for (int k=0;k<stone_see_num;k++)//所有任务时间遍历

                    {
                        for(int j=0;j<num;j++)
                            if(clear_car_team[i].task_time[k]==arr[j]&&stone_team[k].type==0)//车辆时间序列等于arr中的值，且该任务的类型为0
                            {
                                clear_car_team[i].task_locking.push_back(k);
                                clear_car_team[i].task_flag=1;   //车辆锁定
                                stone_team[k].type=1;//任务锁定
                            }
                    }
            }
        }

        task_no_temp.clear();
        for(int j=0;j<stone_see_num;j++)
        {

            if(stone_team[j].type==0) //任务未锁定
                task_no_temp.push_back(j);//将未锁定的任务序号放入task_time_temp
        }
    }


    /*多车对单任务的情况*/
    vector<int>  task_temp;//未安排汽车对某个任务所需时间
    vector<int> car_no_temp;//空闲汽车的序号

    int_least32_t t_task_average_temp;
    for(int j=0;j<stone_see_num;j++)//遍历所有空闲任务
    {
        if(stone_team[j].type==0)
        {
            car_no_temp.clear();
            task_temp.clear();
            for(int i=0;i<clear_car_num;i++) //遍历所有空闲车辆
                if( clear_car_team[i].task_flag==0)
                {
                    {
                        task_temp.push_back((1/(float)clear_car_team[i].task_time[j])*1000);//对完成时间取倒数*1000保证小数点
                        t_task_average_temp=(1/(float)time_clear_limit_up)*1000;
                        car_no_temp.push_back(i);//未安排的汽车序号

                    }
                }
            SumToM(task_temp,task_temp.size(),t_task_average_temp,arr1,sum1,num1);
            if(sum1!=0)
            {  if(time_clear_limit_down<=(double)(1000/sum1)
                        && (double)(1000/sum1) <=time_clear_limit_up)
                {
                    stone_team[j].type=1;//符合区间条件则任务锁定
                    /*找到符合要求的几辆汽车的序号，将他们的锁定，并且确定他们的任务*/


                    for(int k=0;k<task_temp.size();k++)//遍历所有空闲车辆对任务j的时间倒数
                    {
                        for(int z=0;z<num1;z++)//遍历求到的几辆汽车对任务j的时间倒数
                        {  if(clear_car_team[car_no_temp[k]].task_flag==0)
                            {
                                if(task_temp[k]==arr1[z])//如果两者相同
                                {
                                    clear_car_team[car_no_temp[k]].task_flag=1;   //将车辆锁定
                                    clear_car_team[car_no_temp[k]].task_locking.push_back(j);
                                }
                            }
                        }
                    }

                }
            }
        }
    }
    /* 多车对多任务*/

    task_no_temp.clear();//未锁定任务序号
    car_no_temp.clear();//未锁定车辆序号

    for(int i=0;i<clear_car_num;i++) //遍历所有空闲车辆
        if( clear_car_team[i].task_flag==0)
            car_no_temp.push_back(i);//未安排的汽车序号
    for(int j=0;j<stone_see_num;j++)
        if(stone_team[j].type==0) //任务未锁定
            task_no_temp.push_back(j);//将未锁定的任务序号放入task_time_temp
    if(task_no_temp.size()>=car_no_temp.size()&&car_no_temp.size()!=0)//剩余的任务较多
    {

        for(int i=0;i<task_no_temp.size();i++)
        {   int num=i%car_no_temp.size();

            clear_car_team[car_no_temp[num]].task_locking.push_back(task_no_temp[i]);//按顺序分摊所有任务到所有车辆
            clear_car_team[car_no_temp[num]].task_flag=1;
            stone_team[task_no_temp[i]].type=1;
        }

    }

    if(car_no_temp.size()>task_no_temp.size()&&task_no_temp.size()!=0)//剩余的车辆较多
    {

        for(int i=0;i<car_no_temp.size();i++)
        {
            int num=i%task_no_temp.size();
            clear_car_team[car_no_temp[i]].task_locking.push_back(task_no_temp[num]);//按顺序分摊所有车辆到任务
            clear_car_team[car_no_temp[i]].task_flag=1;
            stone_team[task_no_temp[num]].type=1;
        }

    }

}

task_plan::bomb_car_plan()
{
    vector<int>  task_no_temp;//未锁定任务序号
    vector<int>  task_time_temp;//某个车辆对所有未锁定任务的时间数组

    int arr[20]={0};
    int sum=0;
    int num=0;//一对多用
    int arr1[20]={0};
    int sum1=0;
    int num1=0; //多对一用

    for(int j=0;j<bomb_see_num;j++)
        bomb_team[j].type=0;
    for(int j=0;j<bomb_car_num;j++)
        bomb_car_team[j].task_flag=0;

    /*一对一情况*/
    for(int i=0;i<bomb_car_num;i++)
    {
        for(int j=0;j<bomb_see_num;j++)
        {
            if((time_bomb_limit_down<=bomb_car_team[i].task_time[j]
                &&bomb_car_team[i].task_time[j]<=time_bomb_limit_up)
                    &&bomb_team[j].type==0
                    &&bomb_car_team[i].task_flag==0)//满足时间区间并且任务未锁定
            {
                bomb_car_team[i].task_locking.push_back(j);
                bomb_car_team[i].task_flag=1;   //车辆锁定
                bomb_team[j].type=1;//任务锁定
            }
        }
        task_no_temp.clear();
        for(int j=0;j<bomb_see_num;j++)
        {
            if(bomb_team[j].type==0) //任务未锁定
                task_no_temp.push_back(j);//将未锁定的任务序号放入task_time_temp
        }

    }

    /*单车对多任务情况*/

    for(int i=0;i<bomb_car_num;i++)
    {
        if( bomb_car_team[i].task_flag==0)
        {


            for(int k=0; k<task_no_temp.size();k++)
            {
                task_time_temp.push_back(bomb_car_team[i].task_time[task_no_temp[k]]);//给未锁定任务时间数组赋值
            }


            SumToM(task_time_temp,task_time_temp.size(),time_bomb_limit_up,arr,sum,num);
            task_time_temp.clear();//使用完毕清零
            if(sum!=0)
            {
                if(time_bomb_limit_down<=sum
                        &&sum<=time_bomb_limit_up)

                    for (int k=0;k<bomb_see_num;k++)//所有任务时间遍历

                    {
                        for(int j=0;j<num;j++)
                            if(bomb_car_team[i].task_time[k]==arr[j]&&bomb_team[k].type==0)//车辆时间序列等于arr中的值，且该任务的类型为0
                            {
                                bomb_car_team[i].task_locking.push_back(k);
                                bomb_car_team[i].task_flag=1;   //车辆锁定
                                bomb_team[k].type=1;//任务锁定
                            }
                    }
            }
        }

        task_no_temp.clear();
        for(int j=0;j<bomb_see_num;j++)
        {

            if(bomb_team[j].type==0) //任务未锁定
                task_no_temp.push_back(j);//将未锁定的任务序号放入task_time_temp
        }
    }


    /*多车对单任务的情况*/
    vector<int>  task_temp;//未安排汽车对某个任务所需时间
    vector<int> car_no_temp;//空闲汽车的序号

    int_least32_t t_task_average_temp;
    for(int j=0;j<bomb_see_num;j++)//遍历所有空闲任务
    {
        if(bomb_team[j].type==0)
        {
            car_no_temp.clear();
            task_temp.clear();
            for(int i=0;i<bomb_car_num;i++) //遍历所有空闲车辆
                if( bomb_car_team[i].task_flag==0)
                {
                    {
                        task_temp.push_back((1/(float)bomb_car_team[i].task_time[j])*1000);//对完成时间取倒数*1000保证小数点
                        t_task_average_temp=(1/(float)time_bomb_limit_up)*1000;
                        car_no_temp.push_back(i);//未安排的汽车序号

                    }
                }
            SumToM(task_temp,task_temp.size(),t_task_average_temp,arr1,sum1,num1);
            if(sum1!=0)
            {  if(time_bomb_limit_down<=(double)(1000/sum1)
                        && (double)(1000/sum1) <=time_bomb_limit_up)
                {
                    bomb_team[j].type=1;//符合区间条件则任务锁定
                    /*找到符合要求的几辆汽车的序号，将他们的锁定，并且确定他们的任务*/


                    for(int k=0;k<task_temp.size();k++)//遍历所有空闲车辆对任务j的时间倒数
                    {
                        for(int z=0;z<num1;z++)//遍历求到的几辆汽车对任务j的时间倒数
                        {  if(bomb_car_team[car_no_temp[k]].task_flag==0)
                            {
                                if(task_temp[k]==arr1[z])//如果两者相同
                                {
                                    bomb_car_team[car_no_temp[k]].task_flag=1;   //将车辆锁定
                                    bomb_car_team[car_no_temp[k]].task_locking.push_back(j);
                                }
                            }
                        }
                    }

                }
            }
        }
    }
    /* 多车对多任务*/

    task_no_temp.clear();//未锁定任务序号
    car_no_temp.clear();//未锁定车辆序号

    for(int i=0;i<bomb_car_num;i++) //遍历所有空闲车辆
        if( bomb_car_team[i].task_flag==0)
            car_no_temp.push_back(i);//未安排的汽车序号
    for(int j=0;j<bomb_see_num;j++)
        if(bomb_team[j].type==0) //任务未锁定
            task_no_temp.push_back(j);//将未锁定的任务序号放入task_time_temp
    if(task_no_temp.size()>=car_no_temp.size()&&car_no_temp.size()!=0)//剩余的任务较多
    {

        for(int i=0;i<task_no_temp.size();i++)
        {   int num=i%car_no_temp.size();

            bomb_car_team[car_no_temp[num]].task_locking.push_back(task_no_temp[i]);//按顺序分摊所有任务到所有车辆
            bomb_car_team[car_no_temp[num]].task_flag=1;
            bomb_team[task_no_temp[i]].type=1;
        }

    }

    if(car_no_temp.size()>task_no_temp.size()&&task_no_temp.size()!=0)//剩余的车辆较多
    {

        for(int i=0;i<car_no_temp.size();i++)
        {
            int num=i%task_no_temp.size();
            bomb_car_team[car_no_temp[i]].task_locking.push_back(task_no_temp[num]);//按顺序分摊所有车辆到任务
            bomb_car_team[car_no_temp[i]].task_flag=1;
            bomb_team[task_no_temp[num]].type=1;
        }

    }
}

task_plan::repair_car_plan()
{
    vector<int>  task_no_temp;//未锁定任务序号
    vector<int>  task_time_temp;//某个车辆对所有未锁定任务的时间数组

    int arr[20]={0};
    int sum=0;
    int num=0;//一对多用
    int arr1[20]={0};
    int sum1=0;
    int num1=0; //多对一用




    for(int j=0;j<obstacle_num;j++)
        obstacle_team[j].type=0;
    for(int j=0;j<repair_car_num;j++)
        repair_car_team[j].task_flag=0;

    /*一对一情况*/
    for(int i=0;i<repair_car_num;i++)
    {
        for(int j=0;j<obstacle_num;j++)
        {
            if((time_repair_limit_down<=repair_car_team[i].task_time[j]
                &&repair_car_team[i].task_time[j]<=time_repair_limit_up)
                    &&obstacle_team[j].type==0
                    &&repair_car_team[i].task_flag==0)//满足时间区间并且任务未锁定
            {
                repair_car_team[i].task_locking.push_back(j);
                repair_car_team[i].task_flag=1;   //车辆锁定
                obstacle_team[j].type=1;//任务锁定
            }
        }
        task_no_temp.clear();
        for(int j=0;j<obstacle_num;j++)
        {
            if(obstacle_team[j].type==0) //任务未锁定
                task_no_temp.push_back(j);//将未锁定的任务序号放入task_time_temp
        }

    }

    /*单车对多任务情况*/

    for(int i=0;i<repair_car_num;i++)
    {
        if( repair_car_team[i].task_flag==0)
        {


            for(int k=0; k<task_no_temp.size();k++)
            {
                task_time_temp.push_back(repair_car_team[i].task_time[task_no_temp[k]]);//给未锁定任务时间数组赋值
            }


            SumToM(task_time_temp,task_time_temp.size(),time_repair_limit_up,arr,sum,num);
            task_time_temp.clear();//使用完毕清零
            if(sum!=0)
            {
                if(time_repair_limit_down<=sum
                        &&sum<=time_repair_limit_up)

                    for (int k=0;k<obstacle_num;k++)//所有任务时间遍历

                    {
                        for(int j=0;j<num;j++)
                            if(repair_car_team[i].task_time[k]==arr[j]&&obstacle_team[k].type==0)//车辆时间序列等于arr中的值，且该任务的类型为0
                            {
                                repair_car_team[i].task_locking.push_back(k);
                                repair_car_team[i].task_flag=1;   //车辆锁定
                                obstacle_team[k].type=1;//任务锁定
                            }
                    }
            }
        }

        task_no_temp.clear();
        for(int j=0;j<obstacle_num;j++)
        {

            if(obstacle_team[j].type==0) //任务未锁定
                task_no_temp.push_back(j);//将未锁定的任务序号放入task_time_temp
        }
    }


    /*多车对单任务的情况*/
    vector<int>  task_temp;//未安排汽车对某个任务所需时间
    vector<int> car_no_temp;//空闲汽车的序号

    int_least32_t t_task_average_temp;
    for(int j=0;j<obstacle_num;j++)//遍历所有空闲任务
    {
        if(obstacle_team[j].type==0)
        {
            car_no_temp.clear();
            task_temp.clear();
            for(int i=0;i<repair_car_num;i++) //遍历所有空闲车辆
                if( repair_car_team[i].task_flag==0)
                {
                    {
                        task_temp.push_back((1/(float)repair_car_team[i].task_time[j])*1000);//对完成时间取倒数*1000保证小数点
                        t_task_average_temp=(1/(float)time_repair_limit_up)*1000;
                        car_no_temp.push_back(i);//未安排的汽车序号

                    }
                }
            SumToM(task_temp,task_temp.size(),t_task_average_temp,arr1,sum1,num1);
            if(sum1!=0)
            {  if(time_repair_limit_down<=(double)(1000/sum1)
                        && (double)(1000/sum1) <=time_repair_limit_up)
                {
                    obstacle_team[j].type=1;//符合区间条件则任务锁定
                    /*找到符合要求的几辆汽车的序号，将他们的锁定，并且确定他们的任务*/


                    for(int k=0;k<task_temp.size();k++)//遍历所有空闲车辆对任务j的时间倒数
                    {
                        for(int z=0;z<num1;z++)//遍历求到的几辆汽车对任务j的时间倒数
                        {  if(repair_car_team[car_no_temp[k]].task_flag==0)
                            {
                                if(task_temp[k]==arr1[z])//如果两者相同
                                {
                                    repair_car_team[car_no_temp[k]].task_flag=1;   //将车辆锁定
                                    repair_car_team[car_no_temp[k]].task_locking.push_back(j);
                                }
                            }
                        }
                    }

                }
            }
        }
    }
    /* 多车对多任务*/

    task_no_temp.clear();//未锁定任务序号
    car_no_temp.clear();//未锁定车辆序号

    for(int i=0;i<repair_car_num;i++) //遍历所有空闲车辆
        if( repair_car_team[i].task_flag==0)
            car_no_temp.push_back(i);//未安排的汽车序号
    for(int j=0;j<obstacle_num;j++)
        if(obstacle_team[j].type==0) //任务未锁定
            task_no_temp.push_back(j);//将未锁定的任务序号放入task_time_temp
    if(task_no_temp.size()>=car_no_temp.size()&&car_no_temp.size()!=0)//剩余的任务较多
    {

        for(int i=0;i<task_no_temp.size();i++)
        {   int num=i%car_no_temp.size();

            repair_car_team[car_no_temp[num]].task_locking.push_back(task_no_temp[i]);//按顺序分摊所有任务到所有车辆
            repair_car_team[car_no_temp[num]].task_flag=1;
            obstacle_team[task_no_temp[i]].type=1;
        }

    }

    if(car_no_temp.size()>task_no_temp.size()&&task_no_temp.size()!=0)//剩余的车辆较多
    {

        for(int i=0;i<car_no_temp.size();i++)
        {
            int num=i%task_no_temp.size();
            repair_car_team[car_no_temp[i]].task_locking.push_back(task_no_temp[num]);//按顺序分摊所有车辆到任务
            repair_car_team[car_no_temp[i]].task_flag=1;
            obstacle_team[task_no_temp[num]].type=1;
        }

    }

}


task_plan::repair_car_plan2()
{
    vector<int>  task_no_temp;//未锁定任务序号
    vector<int>  car_no_temp;//某个车辆对所有未锁定任务的时间数组

    for(int j=0;j<stone_see_num;j++)
        stone_team[j].type=0;
    for(int j=0;j<repair_car_num;j++)
        repair_car_team[j].task_flag=0;


    for(int j=0;j<stone_see_num;j++)
    {
        if(stone_comp[stone_table[j]] < 2)
        {
            stone_team[j].type = 1;
        }
    }
    /*一对一情况*/
    for(int i=0;i<repair_car_num;i++)
    {

        for(int j=0;j<stone_see_num;j++)
        {
            if((time_repair_limit_down2<=repair_car_team[i].task_time2[j]
                &&repair_car_team[i].task_time2[j]<=time_repair_limit_up2)
                    &&stone_team[j].type==0
                    &&repair_car_team[i].task_flag==0)//满足时间区间并且任务未锁定
            {
                repair_car_team[i].task_locking2.push_back(j);
                repair_car_team[i].task_flag=1;   //车辆锁定
                stone_team[j].type=1;//任务锁定
            }
        }
        task_no_temp.clear();
        for(int j=0;j<stone_see_num;j++)
        {
            if(stone_team[j].type==0) //任务未锁定
                task_no_temp.push_back(j);//将未锁定的任务序号放入task_time_temp
        }

    }


    /* 多车对多任务*/

    task_no_temp.clear();//未锁定任务序号
    car_no_temp.clear();//未锁定车辆序号

    for(int i=0;i<repair_car_num;i++) //遍历所有空闲车辆
        if( repair_car_team[i].task_flag==0)
            car_no_temp.push_back(i);//未安排的汽车序号
    for(int j=0;j<stone_see_num;j++)
        if(stone_team[j].type==0) //任务未锁定
            task_no_temp.push_back(j);//将未锁定的任务序号放入task_time_temp
    if(task_no_temp.size()>=car_no_temp.size()&&car_no_temp.size()!=0)//剩余的任务较多
    {

        for(int i=0;i<task_no_temp.size();i++)
        {   int num=i%car_no_temp.size();

            repair_car_team[car_no_temp[num]].task_locking2.push_back(task_no_temp[i]);//按顺序分摊所有任务到所有车辆
            repair_car_team[car_no_temp[num]].task_flag=1;
            stone_team[task_no_temp[i]].type=1;
        }

    }

    if(car_no_temp.size()>task_no_temp.size()&&task_no_temp.size()!=0)//剩余的车辆较多
    {

        for(int i=0;i<car_no_temp.size();i++)
        {
            int num=i%task_no_temp.size();
            repair_car_team[car_no_temp[i]].task_locking2.push_back(task_no_temp[num]);//按顺序分摊所有车辆到任务
            repair_car_team[car_no_temp[i]].task_flag=1;
            stone_team[task_no_temp[num]].type=1;
        }

    }

}




/*
 *输入:value 寻找的数组
       N  寻找的数组长度
       M 寻找的值
       array 结果数组
       sum 得到的和
       num 和的组成个数
  功能:找到数组中最接近M的多个数之和
*/


void SumToM(vector<int> value , int N, int_least32_t M,int *array,int &sum,int& num)
{
    const int MAX = M+5;
    int_least32_t f[MAX]={0};
    int_least32_t g[MAX][MAX]={0};
    int_least32_t k=0;
    int_least32_t i=0;
    int_least32_t v=0;
    num=0;
    k=0;
    for (i = 0; i<N; i++)
    {
        for (v = M; v >= value[i]; v--)
        {
            if (f[v]<f[v - value[i]] + value[i])
            {
                f[v] = f[v - value[i]] + value[i];
                g[i][v] = 1;
            }
            else
            {
                f[v] = f[v];
                g[i][v] = 0;
            }
        }
    }
    // printf("最接近%d的和为%d\n", M, f[M]);
    sum=f[M];
    i = N; //输出解
    v = M;
    if(N!=0)
    {    while (i-- > 0)
        {
            if (g[i][v] == 1)
            {
                printf("%d, ", value[i]);
                v -= value[i];
                array[k] = value[i];
                k++;
                num++;


            }
        }
    }
    //    else
    //    {
    //        num=1;
    //        array[0]=value[0];
    //        sum=value[0];


    //    }


}

int time_plus(int a,int b)
{
    float c;
    int d;
    c=1/a+1/b;
    d=1/c;
    return d ;


}
