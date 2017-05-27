/*分析方法父类
 * */
#ifndef ANALYSIS_METHOD_H
#define ANALYSIS_METHOD_H
#include <math.h>
#include <vector>
#include "parameter.h"


class Analysis_Method
{
public:
    Analysis_Method();
    //初始化虚函数
    virtual void init(){}
    //分析虚函数
    virtual vector<vector<vector<double> > > Analyse(vector<int> middle,vector<double> power,int sbox){vector<vector<vector<double> > > OnceResult;return OnceResult;}

};

#endif // ANALYSIS_METHOD_H
