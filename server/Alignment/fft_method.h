/*快速傅立叶变换算法类
 * */
#ifndef FFT_METHOD_H
#define FFT_METHOD_H

#include "alignment_method.h"
#include "complex.h"

class FFT_Method : public Alignment_Method{
public:
  FFT_Method(Parameter *parameter);

  //继承父类成员对齐函数
  vector<double> Align(vector<double> samples);

private:
  int n;
  int Points;//处理点数
  vector<int> select_index;//选取点的下标
  vector<vector<double> > outfft;

  //FFT主要功能实现函数
  vector<double> FFTcompute(vector<double> samples, int TRACE_NUM_POINTS);

  //实数转变虚数函数
  vector<complex> YW_to_ComplexYW(vector<double> SZ, int count);

  vector<complex> function_fft(vector<complex> xin, int FFT_N);

  //蝶形运算函数
  complex Diexing_operator(complex a, complex b);

  //求绝对值函数
  vector<double> ABS(vector<complex> SZ, int count);

  //选择样本函数
  vector<double> Select_Samples(vector<double> data, vector<int> index, int select_Num);

  //选择样本序号函数
  vector<int> Select_Samples_Index(vector<double> &data, int select_Num);
};

#endif // FFT_METHOD_H
