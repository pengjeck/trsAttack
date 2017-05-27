#ifndef SMS4_H
#define SMS4_H
#include "middle_method.h"
class SMS4 : public Middle_Method
{
public:
    SMS4(Parameter *parameter);
    //nonprofile�����µ��м�ֵ���㷽��
    vector<int> NoneProfileMiddle(QString plain_s,int SNum);
    //profile�����µ��м�ֵ���㷽��
    int ProfileMiddle(QString plain_s,int correctkey,int SNum);
private:
    //�麺����
    static const unsigned int HM[256];
    //SMS4��S��
    static const QString SMS4_Sbox[256];
    //�Ƿ����ֵ
    int IsValue;
    //����Կ�²�����
    int SBoxLength;
    //й©��
    int HM00;
    int HM01;
    //����й©ģ��
    QString Model;
};

#endif // SMS4_H
