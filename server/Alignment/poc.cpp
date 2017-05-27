#include "poc.h"

POC::POC(Parameter *parameter){
  //this->p = parameter;
  this->Points = parameter->OriginalPoints;
  this->base_trace = parameter->refer_trace;
}


/*samoles�����������䣬Ҫ��samples����Ϊ2����������*/
vector<double> POC::Align(vector<double> samples){
  int fft_size = this->base_trace.size();
  vector<complex> curve1;
  curve1.resize(fft_size);
  vector<complex> curve2;
  curve2.resize(fft_size);
  for(int i = 0; i < fft_size; ++i){
    curve1[i].r = this->base_trace[i];
    curve1[i].i = 0.0;
    curve2[i].r = samples[i];
    curve2[i].i = 0.0;
  }
  vector<complex> fft_curve1 = fft(curve1);
  vector<complex> fft_curve2 = fft(curve2);
  vector<complex> res;
  res.resize(fft_size);
  for(int i = 0; i < fft_size; ++i){
    double real = fft_curve2[i].r * fft_curve1[i].r + fft_curve2[i].i * fft_curve1[i].i;
    double imag = fft_curve1[i].r * fft_curve2[i].i - fft_curve1[i].i * fft_curve2[i].r;
    complex x;
    x.r = real;
    x.i = imag;
    double sqrt1 = sqrt(x.r * x.r + x.i * x.i);
    res[i].r = x.r / sqrt1;
    res[i].i = x.i / sqrt1;
  }
  vector<complex> ifft_res = ifft(res);
  //double[] arr=new double[fft_size];
  double displacement = 0, max = -100000, tmpi = 0;
  for(int i = 0; i < fft_size; ++i){
    //arr[i]=ifft_res[i].re()/fft_size;
    double cur = ifft_res[i].r / fft_size;
    if(cur > max){
      max = cur;
      displacement = tmpi;
    }
    tmpi++;
  }
  vector<double> dis;
  dis.resize(fft_size);
  for(int i = 0; i < fft_size; ++i){
    dis[i] = 2 * 3.141592 * i * displacement / fft_size;
  }
  vector<complex> tmp;
  tmp.resize(fft_size);
  for(int i = 0; i < fft_size; ++i){
    complex x;
    x.r = fft_curve2[i].r * cos(dis[i]) - fft_curve2[i].i * sin(dis[i]);
    x.i = fft_curve2[i].r * sin(dis[i]) + fft_curve2[i].i * cos(dis[i]);
    tmp[i] = x;
  }
  vector<complex> ifft_tmp;
  ifft_tmp.resize(fft_size);
  ifft_tmp = ifft(tmp);
  vector<double> ret;
  ret.resize(fft_size);
  for(int i = 0; i < fft_size; ++i){
    ret[i] = ifft_tmp[i].r;//fft_size;
  }
  return ret;
}

vector<complex> POC::fft(vector<complex> xin){
  //int FFT_N = xin.size();
  double PI = 3.1415926535897932384626433832795028841971;   //����Բ����ֵ
  int f, m, nv2, nm1, i, k, l, j = 0;

  complex u;
  complex w;
  complex t;

  nv2 = this->Points / 2;                  //��ַ���㣬������Ȼ˳���ɵ�λ�򣬲����׵��㷨
  nm1 = this->Points - 1;
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
    f = this->Points;
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
        for(i = j; i <= this->Points - 1; i = i + le)            //����ͬһ���ν����㣬������ϵ����ͬ���ν�
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

vector<complex> POC::ifft(vector<complex> x){
  int N = x.size();
  vector<complex> y;
  y.resize(N);

  // take conjugate
  for(int i = 0; i < N; i++){
    y[i].r = x[i].r;
    y[i].i = -x[i].i;
  }

  // compute forward FFT
  y = fft(y);

  // take conjugate again
  for(int i = 0; i < N; i++){
    y[i].r = y[i].r;
    y[i].i = -y[i].i;
  }

  // divide by N
  for(int i = 0; i < N; i++){
    y[i].r = y[i].r * (1.0 / N);
    y[i].i = y[i].i * (1.0 / N);
  }

  return y;
}

complex POC::Diexing_operator(complex a, complex b){
  complex c;
  c.r = a.r * b.r - a.i * b.i;
  c.i = a.r * b.i + a.i * b.r;
  return c;
}
