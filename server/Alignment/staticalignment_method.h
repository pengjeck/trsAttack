/*静态对齐算法类
 * */
#ifndef STATICALIGNMENT_METHOD_H
#define STATICALIGNMENT_METHOD_H

#include "alignment_method.h"
#include <math.h>

class StaticAlignment_Method : public Alignment_Method{
public:
  StaticAlignment_Method(Parameter *parameter);

  vector<double> Align(vector<double> samples);

private:
  //扫描起点
  int start;
  //扫描终点
  int end;
  //扫面偏移量（范围）
  int RangeOffset;

  //计算相关性
  double Cal_Correlation(vector<double> p0, vector<double> p1, int pointnum);

  vector<double> base_trace;
};

#endif // STATICALIGNMENT_METHOD_H
