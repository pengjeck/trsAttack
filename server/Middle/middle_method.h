#ifndef MIDDLE_METHOD_H
#define MIDDLE_METHOD_H
#include "parameter.h"

class Middle_Method
{
public:
    Middle_Method();
    //nonprofile�����µ��м�ֵ���㷽���麯��
    virtual vector<int> NoneProfileMiddle(QString plain_s,int SNum){vector<int> temp;return temp;}
    //profile�����µ��м�ֵ���㷽���麯��
    virtual int ProfileMiddle(QString plain_s,int correctkey,int SNum){int temp;return temp;}
};

#endif // MIDDLE_METHOD_H
