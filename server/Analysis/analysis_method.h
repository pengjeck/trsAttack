/*������������
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
    //��ʼ���麯��
    virtual void init(){}
    //�����麯��
    virtual vector<vector<vector<double> > > Analyse(vector<int> middle,vector<double> power,int sbox){vector<vector<vector<double> > > OnceResult;return OnceResult;}

};

#endif // ANALYSIS_METHOD_H
