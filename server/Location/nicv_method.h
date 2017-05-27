/*NICV������
 * */
#ifndef NICV_METHOD_H
#define NICV_METHOD_H

#include "location_method.h"

class NICV_Method : public Location_Method{
public:
  NICV_Method(Parameter *parameter);

  //��ʼ������
  void init();

  //nonprofile��λ����
  vector<double> NoneProfileLocation(QString plain, vector<double> power);

private:
  //�²�����Կ����
  int SBoxLength;
  //��λ����
  int Points;
  int num;
  int bit;
  int length;
  //��λ���ֽ����
  int ByteNum;
  QString Auto_Result_Path;
  vector<int> num2;
  vector<double> sum_power;
  vector<double> v_power;
  //��λ���
  vector<double> result;
  vector<vector<double> > resultforplot;
  vector<vector<double> > E_power;

  double getSquareSum(vector<double> inputData);

  int getCount(vector<double> inputData);

  double getVariance(vector<double> inputData);

  double getAverage(vector<double> inputData);

  double getSum(vector<double> inputData);
};

#endif // NICV_METHOD_H
