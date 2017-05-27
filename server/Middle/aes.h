#ifndef AES_H
#define AES_H
#include "middle_method.h"
class AES : public Middle_Method
{
public:
    AES(Parameter *parameter);
    //nonprofile方法下的中间值计算方法
    vector<int> NoneProfileMiddle(QString plain_s,int SNum);
    //profile方法下的中间值计算方法
    int ProfileMiddle(QString plain_s,int correctkey,int SNum);
private:
    //查汉明重
    static const unsigned int HM[256];
    //AES的S盒
    static const QString S_box[256];
    //是否计算值
    int IsValue;
    //猜测子密钥数量
    int SBoxLength;
    //泄漏点
    int HM00;
    int HM01;
    //功耗泄漏模型
    QString Model;
};

#endif // AES_H
