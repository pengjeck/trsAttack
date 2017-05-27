/*NICV方法类
 * */
#ifndef NICV_METHOD_H
#define NICV_METHOD_H

#include "location_method.h"

class NICV_Method : public Location_Method{
public:
  NICV_Method(Parameter *parameter);

  //初始化函数
  void init();

  //nonprofile定位函数
  vector<double> NoneProfileLocation(QString plain, vector<double> power);

private:
  //猜测子密钥数量
  int SBoxLength;
  //定位点数
  int Points;
  int num;
  int bit;
  int length;
  //定位的字节序号
  int ByteNum;
  QString Auto_Result_Path;
  vector<int> num2;
  vector<double> sum_power;
  vector<double> v_power;
  //定位结果
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
