/*������߷�����
 * */
#ifndef DIFFERENTIAL_METHOD_H
#define DIFFERENTIAL_METHOD_H

#include "location_method.h"
#include "dpa_method.h"


class Differential_Method : public Location_Method{
public:
  Differential_Method(Parameter *parameter);

  //��ʼ������
  void init();

  //profile��λ����
  vector<double> ProfileLocation(QString plain, vector<double> power, int correctkey);

private:
  DPA_Method *dpa_method;
  Middle_Factory *MiddleF;
  Middle_Method *MiddleM;
  QString Model; //����й¶ģ��
  QString Algo; //�����㷨
  int ByteNum; //��λ�ֽ����
  QString Result_Path; //���涨λ����·��
  // IO *FileIO;
};

#endif // DIFFERENTIAL_METHOD_H
