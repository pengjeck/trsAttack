#ifndef AES_H
#define AES_H
#include "middle_method.h"
class AES : public Middle_Method
{
public:
    AES(Parameter *parameter);
    //nonprofile�����µ��м�ֵ���㷽��
    vector<int> NoneProfileMiddle(QString plain_s,int SNum);
    //profile�����µ��м�ֵ���㷽��
    int ProfileMiddle(QString plain_s,int correctkey,int SNum);
private:
    //�麺����
    static const unsigned int HM[256];
    //AES��S��
    static const QString S_box[256];
    //�Ƿ����ֵ
    int IsValue;
    //�²�����Կ����
    int SBoxLength;
    //й©��
    int HM00;
    int HM01;
    //����й©ģ��
    QString Model;
};

#endif // AES_H
