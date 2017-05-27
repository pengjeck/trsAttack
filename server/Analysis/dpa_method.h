/*DPA������
 * */
#ifndef DPA_METHOD_H
#define DPA_METHOD_H


#include "analysis_method.h"

class DPA_Method : public Analysis_Method{
public:
  DPA_Method(Parameter *parameter);

  //��ʼ��
  void init();

  //��������
  vector <vector<vector < double>> >
  Analyse(vector<int>
  middle,
  vector<double> power,
  int sbox
  );

  //������ߺ���
  vector<double> difftrace(int middle, vector<double> power);

private:
  //��������
  int Points;
  //��������Կ����
  int NumofSBox;
  //�²�����Կ����
  int SBoxLength;
  vector <vector<vector < double>> >
  power1;
  vector <vector<vector < double>> >
  power2;
  vector <vector<vector < double>> >
  result;
  vector <vector<int>> flag_1;
  vector <vector<int>> flag_2;

  //ƽ���������
  vector<double> Subtraction(vector<double> tmp1, vector<double> tmp2, int flag1, int flag2);

  //�ۼӺ���
  vector<double> add(vector<double> tmp1, vector<double> tmp2);


};

#endif // DPA_METHOD_H
