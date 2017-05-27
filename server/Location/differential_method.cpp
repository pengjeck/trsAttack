#include "differential_method.h"

/*参数说明
 * dap_method：DPA方法类对象
 * MiddleF：中间值工厂类对象
 * MiddleM：中间值类对象
 * Model：功耗模型
 * ByteNum：定位目标字节序号
 * */
Differential_Method::Differential_Method(Parameter *parameter)
{
    parameter->NumofSBox=1;
    dpa_method=new DPA_Method(parameter);
    MiddleF=new Middle_Factory();
    MiddleM=MiddleF->createMiddleMethod(parameter);
    this->Model=parameter->Model;
    this->ByteNum=parameter->ByteNum;
    this->Algo=parameter->Algo;
    this->Result_Path=parameter->Result_Path;
}

void Differential_Method::init()
{
    dpa_method->init();
}

vector<double> Differential_Method::ProfileLocation(QString plain,vector<double> power,int correctkey)
{
    vector<double> Dtrace;
  // vector<int> writemiddle;
  //  writemiddle.clear();
    int middle=MiddleM->ProfileMiddle(plain,correctkey,this->ByteNum);
  //  writemiddle.push_back(middle);
    Dtrace=dpa_method->difftrace(middle,power);
  //  FileIO->writeKeyRand(Result_Path,writemiddle,100);
    return Dtrace;
}
