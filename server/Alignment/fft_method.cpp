#include "fft_method.h"

FFT_Method::FFT_Method(Parameter *parameter){
  //this->p=parameter;
  this->Points = parameter->OriginalPoints;
}


vector<complex> FFT_Method::YW_to_ComplexYW(vector<double> SZ, int count){
  vector<complex> C_SZ;
  complex d[count];
  C_SZ.resize(count);
  for(int i = 0; i < count; i++){
    d[i].r = SZ[i];
    d[i].i = 0;
    C_SZ[i] = d[i];
  }
  return C_SZ;
}

vector<complex> FFT_Method::function_fft(vector<complex> xin, int FFT_N){
  double PI = 3.1415926535897932384626433832795028841971;   //����Բ����ֵ
  int f, m, nv2, nm1, i, k, l, j = 0;
  complex u;
  complex w;
  complex t;

  nv2 = FFT_N / 2;                  //��ַ���㣬������Ȼ˳���ɵ�λ�򣬲����׵��㷨
  nm1 = FFT_N - 1;
  for(i = 0; i < nm1; i++){

    if(i < j)                    //���i<j,�����б�ַ
    {
      t = xin[j];
      xin[j] = xin[i];
      xin[i] = t;
    }
    k = nv2;                    //��j����һ����λ��
    while(k <= j)               //���k<=j,��ʾj�����λΪ1
    {
      j = j - k;                 //�����λ���0
      k = k / 2;                 //k/2���Ƚϴθ�λ���������ƣ�����Ƚϣ�ֱ��ĳ��λΪ0
    }
    j = j + k;                   //��0��Ϊ1
  }

  {
    int le, lei, ip;                            //FFT����ˣ�ʹ�õ����������FFT����
    f = FFT_N;
    for(l = 1; (f = f / 2) != 1; l++)                  //����l��ֵ����������μ���
      ;
    for(m = 1; m <= l; m++)                         // ���Ƶ��νἶ��
    {                                        //m��ʾ��m�����Σ�lΪ���μ�����l=log��2��N
      le = 2 << (m - 1);                            //le���ν���룬����m�����εĵ��ν����le��
      lei = le / 2;                               //ͬһ���ν��вμ����������ľ���
      u.r = 1.0;                             //uΪ���ν�����ϵ������ʼֵΪ1
      u.i = 0.0;
      w.r = cos(PI / lei);               //wΪϵ���̣�����ǰϵ����ǰһ��ϵ������
      w.i = -sin(PI / lei);
      for(j = 0; j <= lei - 1; j++)                 //���Ƽ��㲻ͬ�ֵ��νᣬ������ϵ����ͬ�ĵ��ν�
      {
        for(i = j; i <= FFT_N - 1; i = i + le)            //����ͬһ���ν����㣬������ϵ����ͬ���ν�
        {
          ip = i + lei;                           //i��ip�ֱ��ʾ�μӵ�������������ڵ�
          t = Diexing_operator(xin[ip], u);    //�������㣬�����ʽ
          xin[ip].r = xin[i].r - t.r;
          xin[ip].i = xin[i].i - t.i;
          xin[i].r = xin[i].r + t.r;
          xin[i].i = xin[i].i + t.i;
        }
        u = Diexing_operator(u, w);           //�ı�ϵ����������һ����������
      }
    }
  }

  return xin;
}

complex FFT_Method::Diexing_operator(complex a, complex b){
  complex c;
  c.r = a.r * b.r - a.i * b.i;
  c.i = a.r * b.i + a.i * b.r;
  return c;
}

vector<double> FFT_Method::ABS(vector<complex> SZ, int count){
  vector<double> C_SZ;
  C_SZ.resize(count);
  for(int i = 0; i < count; i++){
    C_SZ[i] = sqrt((SZ[i].r * SZ[i].r) + (SZ[i].i * SZ[i].i));
  }
  return C_SZ;
}

/*�����samples����������Ϊһ�룬��Ҫ��samples����Ϊ2����������*/
vector<double> FFT_Method::Align(vector<double> samples){
  vector<complex> fft_samples = YW_to_ComplexYW(samples, this->Points);
  vector<complex> fft_out = function_fft(fft_samples, this->Points);
  vector<double> f = ABS(fft_out, this->Points); //�����Ӧ�ķ�ֵ

  //��׼��
  vector<double> po;
  po.resize(this->Points / 2);
  for(int i = 0; i < this->Points / 2; i++)
    po[i] = 2 * f[i] * f[i] / pow(10, 10);

  po[0] = 0;
  return po;
}


vector<double> FFT_Method::FFTcompute(vector<double> samples, int TRACE_NUM_POINTS){
  vector<double> psd = Align(samples);
  vector<double> F;
  this->n++;
  if(this->n == 1){
    this->select_index = Select_Samples_Index(psd, TRACE_NUM_POINTS / 2);
  }
  F = Select_Samples(psd, select_index, TRACE_NUM_POINTS / 2);
  for(int i = 0; i < TRACE_NUM_POINTS / 2; i++)
    F[i] = F[i] / pow(10, 10);
  return F;
}

vector<int> FFT_Method::Select_Samples_Index(vector<double> &data, int select_Num){
  vector<int> select_index;
  select_index.resize(select_Num);
  for(int i = 0; i < select_Num; i++){
    double Max = data[0];
    select_index[i] = 0;
    for(int j = 0; j < select_Num - i; j++){
      if(Max < data[j]){
        Max = data[j];
        select_index[i] = j;
      }
    }
    data[select_index[i]] = data[select_Num - i - 1];
  }
  return select_index;
}

vector<double> FFT_Method::Select_Samples(vector<double> data, vector<int> index, int select_Num){
  vector<double> select_samples;
  for(int i = 0; i < select_Num; i++){
    select_samples.push_back(data[index[i]]);
  }
  return select_samples;
}
