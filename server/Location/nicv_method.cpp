#include "nicv_method.h"

/**
 * 参数
 * @param parameter
 */
NICV_Method::NICV_Method(Parameter *parameter){
  this->SBoxLength = parameter->SBoxLength;
  this->Points = parameter->Points;
  this->ByteNum = parameter->ByteNum;
}

/*参数说明：
 * SBoxLength：2的子密钥比特数次幂
 * Points：定位所用点数
 * */
void NICV_Method::init(){
  bit = this->SBoxLength;
  length = this->Points;
  num = 0;
  num2.clear();
  sum_power.clear();
  result.clear();
  resultforplot.clear();
  v_power.clear();
  E_power.clear();

  // num2 = [0, 0, 0]
  for(int i = 0; i < this->SBoxLength; i++)
    num2.push_back(0);

  // sum_power = [0, 0, 0]
  // result = [0, 0, 0]
  // v_power = [0, 0, 0]
  for(int i = 0; i < this->Points; i++){
    sum_power.push_back(0);
    result.push_back(0);
    v_power.push_back(0);
  }

  for(int i = 0; i < this->SBoxLength; i++)
    E_power.push_back(result);
}

/**
 *
 * @param plain:
 * @param power: 电压
 * @return
 */
vector<double> NICV_Method::NoneProfileLocation(QString plain, vector<double> power){
  bool ok;
  QString tem = plain.mid(this->ByteNum * 3, 2);
  int tmp = tem.toInt(&ok, 16);
  num2[tmp] = num2[tmp] + 1;
  num = num + 1;
  for(int i = 0; i < power.size(); i++)
    E_power[tmp][i] = E_power[tmp][i] + power[i];
  for(int i = 0; i < power.size(); i++)
    sum_power[i] = sum_power[i] + power[i];
  for(int i = 0; i < power.size(); i++)
    v_power[i] = v_power[i] + pow((power[i] - sum_power[i] / num), 2);
  //return v_power;
  for(int i = 0; i < power.size(); i++){
    int flag = 0;
    for(int j = 0; j < bit; j++)
      if(num2[j] != 0)
        flag = flag + 1;
    vector<double> double_tmp;
    double_tmp.resize(flag, 0);
    flag = 0;
    for(int j = 0; j < bit; j++)
      if(num2[j] != 0){
        double_tmp[flag] = E_power[j][i] / num2[j];
        flag = flag + 1;
      }
    result[i] = sqrt(getVariance(double_tmp) / v_power[i]);
  }
  return result;
}

double NICV_Method::getSum(vector<double> inputData){
  if(inputData.size() == 0)
    return -1;
  int len = inputData.size();
  double sum = 0;
  for(int i = 0; i < len; i++){
    sum = sum + inputData[i];
  }
  return sum;
}

double NICV_Method::getAverage(vector<double> inputData){
  if(inputData.size() == 0)
    return -1;
  int len = inputData.size();
  double result;
  result = getSum(inputData) / len;

  return result;
}

/**
 * 方差（没有开根号，不是标准差）
 * @param inputData
 * @return
 */
double NICV_Method::getVariance(vector<double> inputData){
  int count = getCount(inputData);
  double sqrsum = getSquareSum(inputData);
  double average = getAverage(inputData);
  double result;
  result = (sqrsum - count * average * average) / count;
  return result;
}

int NICV_Method::getCount(vector<double> inputData){
  return inputData.size();
}

/**
 * 平方和
 * @param inputData
 * @return
 */
double NICV_Method::getSquareSum(vector<double> inputData){
  if(inputData.size() == 0)
    return -1;
  int len = inputData.size();
  double sqrsum = 0.0;
  for(int i = 0; i < len; i++){
    sqrsum = sqrsum + inputData[i] * inputData[i];
  }
  return sqrsum;
}
