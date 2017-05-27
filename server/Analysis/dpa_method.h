/*DPA方法类
 * */
#ifndef DPA_METHOD_H
#define DPA_METHOD_H


#include "analysis_method.h"

class DPA_Method : public Analysis_Method{
public:
  DPA_Method(Parameter *parameter);

  //初始化
  void init();

  //分析函数
  vector <vector<vector < double>> >
  Analyse(vector<int>
  middle,
  vector<double> power,
  int sbox
  );

  //差分曲线函数
  vector<double> difftrace(int middle, vector<double> power);

private:
  //分析点数
  int Points;
  //分析子密钥数量
  int NumofSBox;
  //猜测子密钥数量
  int SBoxLength;
  vector <vector<vector < double>> >
  power1;
  vector <vector<vector < double>> >
  power2;
  vector <vector<vector < double>> >
  result;
  vector <vector<int>> flag_1;
  vector <vector<int>> flag_2;

  //平均相减函数
  vector<double> Subtraction(vector<double> tmp1, vector<double> tmp2, int flag1, int flag2);

  //累加函数
  vector<double> add(vector<double> tmp1, vector<double> tmp2);


};

#endif // DPA_METHOD_H
