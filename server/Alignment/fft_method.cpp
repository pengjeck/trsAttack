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
  double PI = 3.1415926535897932384626433832795028841971;   //定义圆周率值
  int f, m, nv2, nm1, i, k, l, j = 0;
  complex u;
  complex w;
  complex t;

  nv2 = FFT_N / 2;                  //变址运算，即把自然顺序变成倒位序，采用雷德算法
  nm1 = FFT_N - 1;
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
    f = FFT_N;
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
        for(i = j; i <= FFT_N - 1; i = i + le)            //控制同一蝶形结运算，即计算系数相同蝶形结
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

/*输入的samples处理后点数降为一半，且要求samples点数为2的整数次幂*/
vector<double> FFT_Method::Align(vector<double> samples){
  vector<complex> fft_samples = YW_to_ComplexYW(samples, this->Points);
  vector<complex> fft_out = function_fft(fft_samples, this->Points);
  vector<double> f = ABS(fft_out, this->Points); //计算对应的幅值

  //标准化
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
