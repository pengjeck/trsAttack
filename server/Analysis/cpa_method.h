/*CPA������
 * */
#ifndef CPA_METHOD_H
#define CPA_METHOD_H
#include "analysis_method.h"
class CPA_Method : public Analysis_Method
{
public:
    CPA_Method(Parameter *parameter);
    //��ʼ��
    void init();
    //��������
    vector<vector<vector<double> > > Analyse(vector<int> middle,vector<double> power,int sbox);
private:
    //��������
    int Points;
    //����������Կ����
    int NumofSBox;
    //�²�����Կ����
    int SBoxLength;
    /*��������*/
    vector<vector<double> > sum_x;
    vector<vector<double> > sum_y;
    vector<vector<vector<double>  > > sum_xy;
    vector<vector<double> > sum_x2;
    vector<vector<double> > sum_y2;
    vector<int> sum_flag;
    //�����������ά����
    vector<vector<vector<double> > > result;
};

#endif // CPA_METHOD_H
