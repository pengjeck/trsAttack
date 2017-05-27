#include "dtw.h"

dtw::dtw(Parameter *parameter){
  //this->p = parameter;
  this->base_trace = parameter->refer_trace;
}

/**
 * ���빦�����ߣ����ض���󹦺����ߣ�
 * @param samples
 * @return
 */
vector<double> dtw::Align(vector<double> samples){
  this->DTWDistanceFun(this->base_trace, this->base_trace.size(),
                       samples, samples.size(),
                       this->base_trace.size() / 10);
  vector<double> pc;
  pc.resize(this->base_trace.size());
  for(int i = 0; i < F.size(); i++){
    pc[F[i][0]] = samples[F[i][1]];
  }
  F.clear();
  return pc;
}


/*****************************************************************************/
/* DTWDistance������������֮���ƥ�����
/* A,B�ֱ�Ϊ��һ�ڶ������飬I��JΪ�����鳤�ȣ�rΪƥ�䴰�ڵĴ�С
/* r�Ĵ�Сһ��ȡΪ���鳤�ȵ�1/10��1/30
/* ������������֮���ƥ�����,������أ�1.0���������鳤��̫����
/*****************************************************************************/
void dtw::DTWDistanceFun(vector<double> A, int I, vector<double> B, int J, int r){
  int i, j;
  double dist;
  int istart, imax;
  int r2 = r + ABS(I - J);/*ƥ�����*/
  double g1, g2, g3;
  int pathsig = 1;/*·���ı�־*/

  this->distance.resize(I);
  this->dtwpath.resize(I);
  // 	this->F.resize(I);
  /*����һЩ��Ҫ�ĳ�ʼ��*/
  for(i = 0; i < I; i++){
    this->distance[i].resize(J);
    this->dtwpath[i].resize(J);
    for(j = 0; j < J; j++){
      dtwpath[i][j] = 0;
      distance[i][j] = DTWVERYBIG;
    }
  }

  /*��̬�滮����С����*/
  /*�����Ҳ��õ�·���� -------
                            . |
                          .   |
                        .     |
                      .       |
   */
  distance[0][0] = (double) 2 * ABS(A[0] - B[0]);
  for(i = 1; i <= r2; i++){
    distance[i][0] = distance[i - 1][0] + ABS(A[i] - B[0]);
  }
  for(j = 1; j <= r2; j++){
    distance[0][j] = distance[0][j - 1] + ABS(A[0] - B[j]);
  }

  for(j = 1; j < J; j++){
    istart = j - r2;
    if(j <= r2)
      istart = 1;
    imax = j + r2;
    if(imax >= I)
      imax = I - 1;

    for(i = istart; i <= imax; i++){
      g1 = distance[i - 1][j] + ABS(A[i] - B[j]);
      g2 = distance[i - 1][j - 1] + 2 * ABS(A[i] - B[j]);
      g3 = distance[i][j - 1] + ABS(A[i] - B[j]);
      g2 = MIN(g1, g2);
      g3 = MIN(g2, g3);
      distance[i][j] = g3;
    }
  }

  dist = distance[I - 1][J - 1] / ((double) (I + J));
  /*Ѱ��·��,�����Ҳ���������������*/
  i = I - 1;
  j = J - 1;
  while(j >= 1 || i >= 1){
    double m;
    if(i > 0 && j > 0){
      m = MIN(MIN(distance[i - 1][j], distance[i - 1][j - 1]), distance[i][j - 1]);
      if(m == distance[i - 1][j]){
        dtwpath[i - 1][j] = pathsig;
        i--;
      }else if(m == distance[i - 1][j - 1]){
        dtwpath[i - 1][j - 1] = pathsig;
        i--;
        j--;
      }else{
        dtwpath[i][j - 1] = pathsig;
        j--;
      }
    }else if(i == 0){
      dtwpath[0][j - 1] = pathsig;
      j--;
    }else{/*j==0*/
      dtwpath[i - 1][0] = pathsig;
      i--;
    }
  }
  dtwpath[0][0] = pathsig;
  dtwpath[I - 1][J - 1] = pathsig;
  vector<int> sig;
  sig.resize(2);
  for(i = 0; i < I; i++){
    for(j = 0; j < J; j++){
      if(this->dtwpath[i][j] == pathsig){
        sig[0] = i;
        sig[1] = j;
        F.push_back(sig);
      }
    }
  }
}/*end DTWDistance*/
