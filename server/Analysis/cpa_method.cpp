#include "cpa_method.h"

CPA_Method::CPA_Method(Parameter *parameter)
{
    //this->p=parameter;
    this->Points=parameter->Points;
    this->NumofSBox=parameter->NumofSBox;
    this->SBoxLength=parameter->SBoxLength;
}
/*参数说明：
 * Points：分析点数
 * NumofSBox：分析的子密钥数
 * SBLenth：猜测子密钥数，即2的子密钥比特数次幂
 * */
//////CPA分析主函数
vector<vector<vector<double> > > CPA_Method::Analyse(vector<int> middle,vector<double> power,int sbox)
{
    sum_flag[sbox]=sum_flag[sbox]+1;

    for(int i=0;i<middle.size();i++)
    {
        sum_x[sbox][i]=sum_x[sbox][i]+middle[i];
    }
    for(int i=0;i<power.size();i++)
    {
        sum_y[sbox][i]=sum_y[sbox][i]+power[i];
    }
    for(int i=0;i<middle.size();i++)
    {
        for(int j=0;j<power.size();j++)
        {
            sum_xy[sbox][i][j]=sum_xy[sbox][i][j]+(middle[i]-sum_x[sbox][i]/sum_flag[sbox])*(power[j]-sum_y[sbox][j]/sum_flag[sbox]);
        }
    }
    for(int i=0;i<middle.size();i++)
    {
        double tmp=middle[i]-sum_x[sbox][i]/sum_flag[sbox];
        sum_x2[sbox][i]=sum_x2[sbox][i]+tmp*tmp;
    }

    for(int i=0;i<power.size();i++)
    {
        double tmp=power[i]-sum_y[sbox][i]/sum_flag[sbox];
        sum_y2[sbox][i]=sum_y2[sbox][i]+tmp*tmp;
    }

    for(int i=0;i<middle.size();i++)
    {
        for(int j=0;j<power.size();j++)
        {
            double tmp=sum_x2[sbox][i]*sum_y2[sbox][j];
            if(tmp==0)
                result[sbox][i][j]=0;
            else
            result[sbox][i][j]=fabs((sum_xy[sbox][i][j]))/sqrt(tmp);
        }
    }
    vector<vector<vector<double> > > OnceResultkey=result;
    return OnceResultkey;

}

//////////初始化
void CPA_Method::init()
{
    sum_x.clear();
    sum_x2.clear();
    sum_y.clear();
    sum_y2.clear();
    sum_xy.clear();
    result.clear();
    sum_flag.clear();
    for(int i=0;i<this->NumofSBox;i++)
    {
        vector<double> tmp;
        for(int j=0;j<this->SBoxLength;j++)
            tmp.push_back(0);
        sum_x.push_back(tmp);
        sum_x2.push_back(tmp);
    }

    for(int i=0;i<this->NumofSBox;i++)
    {
        vector<double> tmp;
        for(int j=0;j<this->Points;j++)
            tmp.push_back(0);
        sum_y.push_back(tmp);
        sum_y2.push_back(tmp);
    }

    for(int i=0;i<this->NumofSBox;i++)
    {
        vector<vector<double> > tmp;
        for(int j=0;j<this->SBoxLength;j++)
        {
            vector<double> tmp2;
            for(int k=0;k<this->Points;k++)
                tmp2.push_back(0);
            tmp.push_back(tmp2);
        }
        sum_xy.push_back(tmp);
        result.push_back(tmp);
        sum_flag.push_back(0);
    }
}
