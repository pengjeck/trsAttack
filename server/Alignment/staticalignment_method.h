/*��̬�����㷨��
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
  //ɨ�����
  int start;
  //ɨ���յ�
  int end;
  //ɨ��ƫ��������Χ��
  int RangeOffset;

  //���������
  double Cal_Correlation(vector<double> p0, vector<double> p1, int pointnum);

  vector<double> base_trace;
};

#endif // STATICALIGNMENT_METHOD_H
