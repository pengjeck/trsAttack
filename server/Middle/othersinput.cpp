#include "othersinput.h"

OthersInput::OthersInput(Parameter *parameter)
{
    this->p=parameter;
}
/*�ⲿ�ļ�����δ֪��Կ���м�ֵ*/
vector<int> OthersInput::NoneProfileMiddle(QString plain_s,int SNum)
{
    bool ok;
    QStringList tmp=plain_s.split(" ");
    vector<int> txtInt;
    for(int j=p->SBoxLength*SNum;j<p->SBoxLength*(SNum+1);j++)
        txtInt.push_back(tmp[j].toInt(&ok,10));
    return txtInt;
}
/*�ⲿ�ļ�������֪��Կ���м�ֵ*/
int OthersInput::ProfileMiddle(QString plain_s,int correctkey,int SNum)
{
    bool ok;
    QStringList tmp=plain_s.split(" ");
    int txtInt = tmp[SNum].toInt(&ok,10);
    return txtInt;
}
