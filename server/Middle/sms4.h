#ifndef SMS4_H
#define SMS4_H
#include "middle_method.h"
class SMS4 : public Middle_Method
{
public:
    SMS4(Parameter *parameter);
    //nonprofile方法下的中间值计算方法
    vector<int> NoneProfileMiddle(QString plain_s,int SNum);
    //profile方法下的中间值计算方法
    int ProfileMiddle(QString plain_s,int correctkey,int SNum);
private:
    //查汉明重
    static const unsigned int HM[256];
    //SMS4的S盒
    static const QString SMS4_Sbox[256];
    //是否计算值
    int IsValue;
    //子密钥猜测数量
    int SBoxLength;
    //泄漏点
    int HM00;
    int HM01;
    //功耗泄漏模型
    QString Model;
};

#endif // SMS4_H
