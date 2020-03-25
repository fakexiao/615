#include "ga_path.h"
#include "math.h"
#include "gridmap.h"
#include "stdio.h"
#include "numeric"
#define random(x) (rand()%x)
extern vector<vector<int>>  maze;
using namespace std;
individul   father_temp[IndvNum];
GA_path::GA_path()
{
    // 起点所在列（从左到右编号1.2.3...）
    //    xs = p_start % 60 ;
    xs=6;
    //起点所在行（从上到下编号行1.2.3...）
    //  ys = p_start / (60 )+1;
    ys=1;

    xe=5;
    ye=12;
    p_start=(ys-1)*60+xs;
    // 终点所在列、行
    //  xe = p_end % 60;

    //ye = p_end / (60)+1;

    p_end=(ye-1)*60+xe;
    pm = 0.3;


}
vector<float> ms(IndvNum,0);

void GA_path::run()
{
    srand((int)time(0));

    int can[20]={0};  // 每一行的可行点
    int  no;// 栅格序号
    int count;
    int can_num;
    int index,z=0,max_no;

    pass_num = ye - ys + 1;

    for(int k=0;k<IndvNum;k++)
    {

        father_temp[k].gene.clear();

    }


    for(int i = 0 ;i<IndvNum;i++) //i代表了航线数量
    {

        father_temp[i].gene.push_back(p_start); ;
        int j = 1;//第几个点
        //除去起点和终点
        for (int yk = ys+1;yk<= ye-1;yk++)
        {

            j = j + 1;

            count=0;
            for(int xk = 1 ; xk<=60;xk++)
            {                         // 栅格序号
                no = (xk ) + (yk-1 ) * 60;
                if(maze[xk-1][yk-1] == 0)


                {

                    // 把点加入can矩阵中
                    can[count] = no;
                    count++;

                    //每一行选取一个无障碍栅格作为初始经过点 can是每一行的可选容器}

                }



            }


            can_num = count-1;
            // 产生随机整数
            index = random(can_num);

            // 为每一行加一个可行点
            father_temp[i].gene.push_back(can[index])  ;//随机选择一个可行点放入father_temp表示第i条航线第j个点（j行）的初始选择点

        }
        father_temp[i].gene.push_back(p_end);
        generate_continuous_path(father_temp[i],60 );
        if (! father_temp[i].gene.empty())
        {   father[z].gene.clear();
            father[z].gene.insert(father[z].gene.end(),father_temp[i].gene.begin(),father_temp[i].gene.end());//产生的初代路径
            z=z+1;
        }


    }
    // 计算初始化种群的适应度
    //计算路径长度
    cal_path_value(father);
    // 计算路径平滑度
    cal_path_smooth(father, 60);
    for(int i=0;i<IndvNum;i++)
    {

        if(path_value[i]==0)
            fit_value.push_back(0) ;
        else fit_value.push_back(a * (1/path_value[i])  + b * (1/path_smooth[i])) ;
    }


    for (int i = 1 ;i< max_gen;i++)
    {     // 选择操作
        selection();
        // 交叉操作
        crossover();
        // 变异操作
        mutation();
        // 更新种群
        for(int i=0;i<IndvNum;i++)
        {

            father[i].gene = son[i].gene;
            son[i].gene.clear();

        }
        // 计算路径长度
        cal_path_value(father);
        // 计算路径平滑度
        cal_path_smooth(father, 60);
        for(int i=0;i<IndvNum;i++)
        {        if(path_value[i]==0)
                fit_value.push_back(0) ;
            fit_value[i] = a * (1/path_value[i])  + b * (1/path_smooth[i]);
        }
    }
    float max=-999;
    for(int i=0;i<IndvNum;i++)
    {
        if(max<fit_value[i])
        { max=fit_value[i];
            max_no=i;   }

    }

    min_path= father[max_no].gene ;

}

void GA_path::generate_continuous_path(individul &path_raw,  int x)
{   int x_now,y_now,x_next,y_next,x_insert,y_insert;
    int_least64_t max_iteration=0;
    int_fast32_t num_insert;
    int i=0;
    int_fast32_t single_path_num;
    single_path_num=path_raw.gene.size();
    while (i!=(single_path_num-1)) {
        // 点i所在列（从左到右编号1.2.3...）




        x_now = path_raw.gene[i]%  60;
        // 点i所在行（从上到下编号行1.2.3...）
        y_now = path_raw.gene[i] / (60 )+1;
        // 点i+1所在列、行
        x_next = path_raw.gene[i+1]%  60;
        // 点i所在行（从上到下编号行1.2.3...）
        y_next = path_raw.gene[i+1] / (60 )+1;


        // 判断点i和i+1是否连续,若不连续插入值
        while(max(abs(x_next - x_now), abs(y_next - y_now)) != 1) //判断两点是否连续
        { x_insert = floor((x_next + x_now) / 2);
            y_insert = floor((y_next + y_now) / 2);

            // 插入栅格为自由栅格
            if (maze[x_insert-1 ][y_insert-1] == 0 )
                // 栅格序号
            {    num_insert = x_insert  + (y_insert-1)  * 60;
                // 插入新序号
                path_raw.gene.insert(path_raw.gene.begin()+1+i,num_insert);
            }

            // 插入栅格为障碍物栅格

            else
            {
                // 往右走
                //if（i和i+1中间的点的右边不是障碍点）&&（i和i+1插入点的右边不是第i个点）&&（i和i+1插入点的右边不是第i+1个点）
                if (maze[x_insert][y_insert-1]== 0
                        && (x_insert+1 + (y_insert - 1) * 60 != path_raw.gene[i])
                        && (x_insert+1 + (y_insert - 1) * 60 != path_raw.gene[i+1]))
                {
                    x_insert = x_insert + 1;
                    // 栅格序号
                    num_insert = (x_insert) + (y_insert - 1) * x;
                    // 插入新序号
                    path_raw.gene.insert(path_raw.gene.begin()+1+i,num_insert);
                }

                // 往左走
                else if  (maze[x_insert- 2][y_insert-1]== 0
                          && ((x_insert-1) + (y_insert-1 ) * 60 != path_raw.gene[i])
                          && ((x_insert-1) + (y_insert-1 ) * 60 != path_raw.gene[i+1]))
                {
                    x_insert = x_insert -1;
                    // 栅格序号
                    num_insert = (x_insert ) + (y_insert - 1) * x;
                    // 插入新序号
                    path_raw.gene.insert(path_raw.gene.begin()+1+i,num_insert);
                }
                // 向上走

                else if  (maze[x_insert-1][y_insert]== 0
                          && ((x_insert) + y_insert  * 60 != path_raw.gene[i])
                          && ((x_insert) + y_insert  * 60 != path_raw.gene[i+1]))
                {
                    y_insert = y_insert +1;
                    // 栅格序号
                    num_insert = (x_insert ) + (y_insert - 1) * x;
                    // 插入新序号
                    path_raw.gene.insert(path_raw.gene.begin()+1+i,num_insert);
                }

                // 向下走
                else if  (maze[x_insert-1][y_insert-2]== 0
                          && ((x_insert) + (y_insert - 2) * 60  != path_raw.gene[i])
                          && ((x_insert) + (y_insert - 2) * 60  != path_raw.gene[i+1]))
                {
                    y_insert = y_insert -1;
                    // 栅格序号
                    num_insert = (x_insert) + (y_insert - 1) * x;
                    // 插入新序号
                    path_raw.gene.insert(path_raw.gene.begin()+1+i,num_insert);
                }
                // 其他情况舍去此路径
                else

                {
                    path_raw.gene.clear();
                    break;

                }
            }
            x_next = x_insert;
            y_next = y_insert;
            max_iteration = max_iteration + 1;
            if (max_iteration > 200)
            {
                path_raw.gene.clear();
                break;
                // 初始化最大迭代次数
                max_iteration = 0;

            }
        }

        if (path_raw.gene.empty())
            break   ;
        single_path_num=path_raw.gene.size();
        i = i + 1;
    }



}

void GA_path::mutation()
{
    int_least32_t max_iteration,m;
    int mpoint[2];
    for (int i = 1;i<IndvNum;i++)
        // 初始化最大迭代次数
    {  max_iteration = 0;

        m = son[i].gene.size();
        // single_new_pop_slice初始化
        individul single_new_pop_slice;
        if(rand() % (1000) / (float)(1000) < pm)
        {
            while (single_new_pop_slice.gene.empty())//可能会连续化失败
            {  //生成1-（m-2）的两个随机数,并排序
                mpoint[0]=rand()%(m-2)+1;//第几个点从0开始
                mpoint[1]=rand()%(m-2)+1;
                mpoint[0]=min(mpoint[0],mpoint[1]);
                mpoint[1]=max(mpoint[0],mpoint[1]);
                single_new_pop_slice.gene.push_back(son[i].gene[mpoint[0]]);
                single_new_pop_slice.gene.push_back(son[i].gene[mpoint[1]]);
                generate_continuous_path(single_new_pop_slice, 60 );

            }
            vector<int> temp1(son[i].gene.begin(),son[i].gene.begin()+mpoint[0]+1);
            vector<int> temp2(single_new_pop_slice.gene.begin()+1,single_new_pop_slice.gene.end()-1);
            vector<int> temp3(son[i].gene.begin()+mpoint[1],son[i].gene.end());
            temp1.insert(temp1.end(),temp2.begin(),temp2.end());
            temp1.insert(temp1.end(),temp3.begin(),temp3.end());
            son[i].gene=temp1;
            //single_new_pop_slice再次初始化
            single_new_pop_slice.gene.clear();
        }
        else
            son[i].gene=son[i].gene  ;
    }


}

void GA_path::selection()
{//构造轮盘

    float total_fit;
    vector<float> p_fit_value(IndvNum,0);

    for(int i=0;i<IndvNum;i++)
        total_fit=total_fit+fit_value[i] ;

    for(int i=0;i<IndvNum;i++)
        p_fit_value[i] = fit_value[i] / total_fit;
    for(int i=1;i<IndvNum;i++)
        p_fit_value[i]= p_fit_value[i]+p_fit_value[i-1];    // 概率求和排序
    // 随机数从小到大排列
    for(int i=0;i<IndvNum;i++)
        ms[i]=rand() % (1000) / (float)(1000);
    sort(ms.begin(),ms.end());//从小到大
    int fitin = 0;
    int newin = 0;
    while (newin <= IndvNum)
    { if(ms[newin] < p_fit_value[fitin])
        {   son[newin].gene.clear();
            son[newin].gene.insert(son[newin].gene.end(),father[fitin].gene.begin(),father[fitin].gene.end());
            newin = newin+1;}
        else
            fitin = fitin+1;
    }

}

void GA_path::crossover()
{

}

void GA_path::cal_path_value(individul *path_raw)
{
    individul single_path;
    float m;
    int x_now,y_now,x_next,y_next;

    for (int i = 0 ;i<IndvNum;i++ )
    {
        single_path.gene= path_raw[i].gene;
        m = single_path.gene.size();
        for(int j=1;j<m-1;j++)
        { // 点i所在列（从左到右编号1.2.3...）
            x_now = single_path.gene[j]% 60 + 1;
            // 点i所在行（从上到下编号行1.2.3...）
            y_now = single_path.gene[j]/60 + 1;
            // 点i+1所在列、行
            x_next = single_path.gene[j+1]% 60 + 1;
            y_next = single_path.gene[j+1]/60 + 1;
            if (abs(x_now - x_next) + abs(y_now - y_next) == 1)
                path_value[i]  = path_value[i] + 1;
            else
                path_value[i]  = path_value[i] + sqrt(2);
        }
    }


}

void GA_path::cal_path_smooth(individul *path_raw, int x)
{   individul single_path;
    float m;
    int x_now,y_now,x_next,y_next,x_next2,y_next2,c2;
    for (int i = 0 ;i<IndvNum;i++)
    { single_path.gene = path_raw[i].gene;
        m = single_path.gene.size();

        for(int j=1;j<m-2;j++)
        {
            // 点i所在列（从左到右编号1.2.3...）
            x_now = single_path.gene[j]% x + 1;
            // 点i所在行（从上到下编号行1.2.3...）
            y_now = single_path.gene[j]/x + 1;
            // 点i+1所在列、行
            x_next = single_path.gene[j+1]% x + 1;
            y_next = single_path.gene[j+1]/x + 1;



            // 点i+2所在列、行
            x_next = single_path.gene[j+2]% x + 1;
            y_next = single_path.gene[j+2]/x + 1;
            //path_smooth(1, i) = path_smooth(1, i) + abs(atan(abs(x_now - x_next1)/abs(y_now - y_next1))-atan(abs(x_next2 - x_next1)/abs(y_next2 - y_next1)));
            //a2 = (x_now - x_next1)^2 + (y_now - y_next1)^2;
            //b2 = (x_next2 - x_next1)^2 + (y_next2 - y_next1)^2;
            c2 = (x_now - x_next2)^2 + (y_now - y_next2)^2;
            //angle = (a2 + c2 - b2) / (2 * sqrt(a2) *  sqrt(c2));
            if (c2 < 8 && c2 > 4)
                path_smooth[i]  = path_smooth[i] + 5;
            else if (c2 <= 4 && c2 > 1)
                path_smooth[i] = path_smooth[i] + 30;
            else if  (c2 <= 1)
                path_smooth[i]= path_smooth[i]+ 5000;
        }
    }
}




int getPositionOfMax(vector<float> vec, float max) {
    auto distance = find(vec.begin(), vec.end(), max);
    return distance - vec.begin();
}




