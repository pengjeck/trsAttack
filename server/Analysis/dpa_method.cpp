#include "dpa_method.h"

DPA_Method::DPA_Method(Parameter *parameter)
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
////////DPA分析主函数
vector<vector<vector<double> > > DPA_Method::Analyse(vector<int> middle,vector<double> power,int sbox)
{
    vector<double> power_double=power;
    for(int i=0;i<this->SBoxLength;i++)
    {
        int hw=middle[i];
        if(hw<4)
        {
            flag_1[sbox][i]=flag_1[sbox][i]+1;
            power1[sbox][i]=add(power1[sbox][i],power_double);
        }
        else
        {
            flag_2[sbox][i]=flag_2[sbox][i]+1;
            power2[sbox][i]=add(power2[sbox][i],power_double);
        }
        if(flag_1[sbox][i]!=0&&flag_2[sbox][i]!=0)
        result[sbox][i]=Subtraction(power1[sbox][i],power2[sbox][i],flag_1[sbox][i],flag_2[sbox][i]);
    }
     vector<vector<vector<double> > > OnceResult=result;
     return OnceResult;
}

///////////初始化
void DPA_Method::init()
{
    power1.clear();
    power2.clear();
    result.clear();
    flag_1.clear();
    flag_2.clear();
    for(int i=0;i<this->NumofSBox;i++)
    {
        vector<vector<double> > tmp;
        vector<int>tmp3;
        for(int j=0;j<this->SBoxLength;j++)
        {
            vector<double> tmp2;
            for(int k=0;k<this->Points;k++)
                tmp2.push_back(0);
            tmp.push_back(tmp2);
            tmp3.push_back(0);
        }
        power1.push_back(tmp);
        power2.push_back(tmp);
        result.push_back(tmp);
        flag_1.push_back(tmp3);
        flag_2.push_back(tmp3);
    }
}


vector<double> DPA_Method::difftrace(int middle,vector<double> power)
{
    vector<double> power_double;
    power_double=power;
        if(middle<4)
        {
            flag_1[0][0]=flag_1[0][0]+1;
            power1[0][0]=add(power1[0][0],power_double);
        }
        else
        {
            flag_2[0][0]=flag_2[0][0]+1;
            power2[0][0]=add(power2[0][0],power_double);
        }
        if(flag_1[0][0]!=0&&flag_2[0][0]!=0)
        result[0][0]=Subtraction(power1[0][0],power2[0][0],flag_1[0][0],flag_2[0][0]);

     return result[0][0];
}

vector<double> DPA_Method::add(vector<double> tmp1,vector<double> tmp2)
{

    vector<double> tmp;tmp.resize(tmp1.size(),0);
    for(int i=0;i<tmp1.size();i++)
        tmp[i]=tmp1[i]+tmp2[i];
    return tmp;
}

vector<double> DPA_Method::Subtraction(vector<double> tmp1,vector<double> tmp2,int flag1,int flag2)
{
    vector<double> tmp;tmp.resize(tmp1.size(),0);
    for(int i=0;i<tmp1.size();i++)
    {
        tmp[i]=fabs(tmp1[i]/flag1-tmp2[i]/flag2);
    }
    return tmp;
}
