/*���ٸ���Ҷ�任�㷨��
 * */
#ifndef FFT_METHOD_H
#define FFT_METHOD_H

#include "alignment_method.h"
#include "complex.h"

class FFT_Method : public Alignment_Method{
public:
  FFT_Method(Parameter *parameter);

  //�̳и����Ա���뺯��
  vector<double> Align(vector<double> samples);

private:
  int n;
  int Points;//�������
  vector<int> select_index;//ѡȡ����±�
  vector<vector<double> > outfft;

  //FFT��Ҫ����ʵ�ֺ���
  vector<double> FFTcompute(vector<double> samples, int TRACE_NUM_POINTS);

  //ʵ��ת����������
  vector<complex> YW_to_ComplexYW(vector<double> SZ, int count);

  vector<complex> function_fft(vector<complex> xin, int FFT_N);

  //�������㺯��
  complex Diexing_operator(complex a, complex b);

  //�����ֵ����
  vector<double> ABS(vector<complex> SZ, int count);

  //ѡ����������
  vector<double> Select_Samples(vector<double> data, vector<int> index, int select_Num);

  //ѡ��������ź���
  vector<int> Select_Samples_Index(vector<double> &data, int select_Num);
};

#endif // FFT_METHOD_H
