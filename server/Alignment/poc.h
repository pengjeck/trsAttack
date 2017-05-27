/*相位相关算法类
 * */
#ifndef POC_H
#define POC_H
#include "alignment_method.h"
#include "complex.h"
#include<vector>
using namespace std;

class POC : public Alignment_Method
{
public:
    POC(Parameter *parameter);
    //继承父类成员对齐函数
    vector<double> Align(vector<double> samples);

private:
    int Points;
    //FFT函数
    vector<complex> fft(vector<complex> xin);
    //逆FFT函数
    vector<complex> ifft(vector<complex> x);
    //基准曲线
    vector<double > base_trace;
    //蝶形运算函数
    complex Diexing_operator(complex a, complex b);
};

#endif // POC_H
