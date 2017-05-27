/* ��̬ʱ������㷨��
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

  //�̳и����Ա���뺯��
  vector<double> Align(vector<double> samples);

private:
  int Radius;//����
  vector<double> base_trace;//��׼����

  vector<vector<double> > distance; /*�������*/
  vector<vector<int> > dtwpath; /*����·��*/

  vector<vector<int> > F; /*����·��*/
  //����DTWƥ��������
  void DTWDistanceFun(vector<double> A, int I, vector<double> B, int J, int r);
};

#endif // dtw_H
