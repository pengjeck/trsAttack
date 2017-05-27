/* 动态时间规整算法类
 * */
#ifndef dtw_H
#define dtw_H

#include "alignment_method.h"

#define DTWMAXNUM 2000
#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))
#define ABS(a) ((a)>0?(a):(-(a)))
#define DTWVERYBIG 100000000.0

class dtw : public Alignment_Method{
public:
  dtw(Parameter *parameter);

  //继承父类成员对齐函数
  vector<double> Align(vector<double> samples);

private:
  int Radius;//步长
  vector<double> base_trace;//基准曲线

  vector<vector<double> > distance; /*保存距离*/
  vector<vector<int> > dtwpath; /*保存路径*/

  vector<vector<int> > F; /*保存路径*/
  //计算DTW匹配距离距离
  void DTWDistanceFun(vector<double> A, int I, vector<double> B, int J, int r);
};

#endif // dtw_H
