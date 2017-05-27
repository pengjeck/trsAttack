/*��λ����㷨��
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
    //�̳и����Ա���뺯��
    vector<double> Align(vector<double> samples);

private:
    int Points;
    //FFT����
    vector<complex> fft(vector<complex> xin);
    //��FFT����
    vector<complex> ifft(vector<complex> x);
    //��׼����
    vector<double > base_trace;
    //�������㺯��
    complex Diexing_operator(complex a, complex b);
};

#endif // POC_H
