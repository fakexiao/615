#ifndef GA_PATH_H
#define GA_PATH_H
#include"vector"
#include "math.h"
#include "stdio.h"
using namespace std;
const int IndvNum = 100;		//最大种群数

int findMax(vector<float> vec) ;
int getPositionOfMax(vector<float> vec, float max);

struct individul
{
    std::vector<int>		gene;			//个体的基因
    int						length;			//基因的长度
    int						accomadation;	//个体适应度
    individul():length(0),accomadation(0) {	}
};

class GA_path
{
public:
    GA_path();

    //创建父代种群
    void run();

    void  generate_continuous_path(individul &path_raw,  int x);
    void mutation();
    void selection();
    void crossover();
      void cal_path_value(individul * path_raw);
     void cal_path_smooth(individul * path_raw, int x);

    individul			father[IndvNum];			//父代种群
    individul			son[IndvNum];				//子代种群
    individul			bestIndv;					//记录当前最好的个体

    int p_start ;   // 起始序号
    int p_end ;    // 终止序号
    int    NP = 800;     // 种群数量
    int max_gen = 80;  // 最大进化代数
    int pc = 0.8;      // 交叉概率
    float  pm ;      // 变异概率
    int  a = 0.3;         // 路径长度比重
    int  b =2;        // 路径顺滑度比重
    int xs;
    int ys;
    int xe;
    int ye;

int pass_num;
float path_value[IndvNum]={0};
float path_smooth[IndvNum]={0};

vector<float> fit_value;
vector<int> min_path;

};

#endif // GA_PATH_H
