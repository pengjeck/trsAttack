#include "poc.h"

POC::POC(Parameter *parameter){
  //this->p = parameter;
  this->Points = parameter->OriginalPoints;
  this->base_trace = parameter->refer_trace;
}


/*samoles处理后点数不变，要求samples点数为2的整数次幂*/
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
  double PI = 3.1415926535897932384626433832795028841971;   //定义圆周率值
  int f, m, nv2, nm1, i, k, l, j = 0;

  complex u;
  complex w;
  complex t;

  nv2 = this->Points / 2;                  //变址运算，即把自然顺序变成倒位序，采用雷德算法
  nm1 = this->Points - 1;
  for(i = 0; i < nm1; i++){

    if(i < j)                    //如果i<j,即进行变址
    {
      t = xin[j];
      xin[j] = xin[i];
      xin[i] = t;
    }
    k = nv2;                    //求j的下一个倒位序
    while(k <= j)               //如果k<=j,表示j的最高位为1
    {
      j = j - k;                 //把最高位变成0
      k = k / 2;                 //k/2，比较次高位，依次类推，逐个比较，直到某个位为0
    }
    j = j + k;                   //把0改为1
  }

  {
    int le, lei, ip;                            //FFT运算核，使用蝶形运算完成FFT运算
    f = this->Points;
    for(l = 1; (f = f / 2) != 1; l++)                  //计算l的值，即计算蝶形级数
      ;
    for(m = 1; m <= l; m++)                         // 控制蝶形结级数
    {                                        //m表示第m级蝶形，l为蝶形级总数l=log（2）N
      le = 2 << (m - 1);                            //le蝶形结距离，即第m级蝶形的蝶形结相距le点
      lei = le / 2;                               //同一蝶形结中参加运算的两点的距离
      u.r = 1.0;                             //u为蝶形结运算系数，初始值为1
      u.i = 0.0;
      w.r = cos(PI / lei);               //w为系数商，即当前系数与前一个系数的商
      w.i = -sin(PI / lei);
      for(j = 0; j <= lei - 1; j++)                 //控制计算不同种蝶形结，即计算系数不同的蝶形结
      {
        for(i = j; i <= this->Points - 1; i = i + le)            //控制同一蝶形结运算，即计算系数相同蝶形结
        {
          ip = i + lei;                           //i，ip分别表示参加蝶形运算的两个节点
          t = Diexing_operator(xin[ip], u);    //蝶形运算，详见公式
          xin[ip].r = xin[i].r - t.r;
          xin[ip].i = xin[i].i - t.i;
          xin[i].r = xin[i].r + t.r;
          xin[i].i = xin[i].i + t.i;
        }
        u = Diexing_operator(u, w);           //改变系数，进行下一个蝶形运算
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
