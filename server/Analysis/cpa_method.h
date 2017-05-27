/*CPA方法类
 * */
#ifndef CPA_METHOD_H
#define CPA_METHOD_H
#include "analysis_method.h"
class CPA_Method : public Analysis_Method
{
public:
    CPA_Method(Parameter *parameter);
    //初始化
    void init();
    //分析函数
    vector<vector<vector<double> > > Analyse(vector<int> middle,vector<double> power,int sbox);
private:
    //分析点数
    int Points;
    //分析的子密钥数量
    int NumofSBox;
    //猜测子密钥数量
    int SBoxLength;
    /*辅助变量*/
    vector<vector<double> > sum_x;
    vector<vector<double> > sum_y;
    vector<vector<vector<double>  > > sum_xy;
    vector<vector<double> > sum_x2;
    vector<vector<double> > sum_y2;
    vector<int> sum_flag;
    //分析结果，三维数据
    vector<vector<vector<double> > > result;
};

#endif // CPA_METHOD_H
