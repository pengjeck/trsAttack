#include "differential_method.h"

/*����˵��
 * dap_method��DPA���������
 * MiddleF���м�ֵ���������
 * MiddleM���м�ֵ�����
 * Model������ģ��
 * ByteNum����λĿ���ֽ����
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
