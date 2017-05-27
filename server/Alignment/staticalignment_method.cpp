#include "staticalignment_method.h"

StaticAlignment_Method::StaticAlignment_Method(Parameter *parameter){
  //this->p=parameter;
  this->RangeOffset = parameter->RangeOffset;
  if(parameter->Start_Point - this->RangeOffset < 0)
    this->start = 0;
  else
    this->start = parameter->Start_Point - this->RangeOffset;
  if(parameter->Start_Point + this->RangeOffset > parameter->TotalPoints)
    this->end = parameter->TotalPoints;
  else
    this->end = parameter->Start_Point + this->RangeOffset;
  this->base_trace = parameter->refer_trace;
}

/******
 * refer_trace����׼���ߣ�Ϊ������Ӧ����������
 * misalign_trace:���ڶ��������,ɨ������������׼����ƥ�����������
 * start:ɨ�������������
 * end:ɨ�����������յ�
 */
vector<double> StaticAlignment_Method::Align(vector<double> samples){
  vector<double> misalign_trace = samples;
  vector<double> align_trace;
  align_trace.resize(this->base_trace.size()); //���������
  vector<double> trace_fragment;
  trace_fragment.resize(this->base_trace.size()); //���ڼ�������Ե���������
  int startindex_of_maxCorrelation = 0; //�������ߵ������������
  double maxCorrelation = 0; //����Լ�ֵ
  double correlation_vector[end - start]; //�洢���������ϵ��������鿴
  for(int i = start; i < end; i++){
    if((i + this->base_trace.size()) > misalign_trace.size() - 1) break; //�������߳���
    //ȡ����������
    for(int j = 0; j < this->base_trace.size(); j++){
      trace_fragment[j] = misalign_trace[j + i];
    }
    //�������ϵ��
    double correlation = Cal_Correlation(this->base_trace,
                                         trace_fragment,
                                         this->base_trace.size());
    correlation_vector[i - start] = correlation;

    if(maxCorrelation < correlation){
      maxCorrelation = correlation;
      startindex_of_maxCorrelation = i;
    }

  }

  //ȡ�����������ƥ���
  for(int i = 0; i < this->base_trace.size(); i++){
    align_trace[i] = misalign_trace[i + startindex_of_maxCorrelation];
  }

  return align_trace;
}

double StaticAlignment_Method::Cal_Correlation(vector<double> p0,
                                               vector<double> p1,
                                               int pointnum){
  double average1 = 0, average2 = 0;
  double tecent1 = 0, tecent2 = 0, tecent3 = 0;
  for(int i = 0; i < pointnum; i++){
    average1 += p0[i];
    average2 += p1[i];
  }
  average1 /= pointnum;
  average2 /= pointnum;
  for(int i = 0; i < pointnum; i++){
    tecent1 += (p0[i] - average1) * (p1[i] - average2);
    tecent2 += pow(p0[i] - average1, 2);
    tecent3 += pow(p1[i] - average2, 2);
  }
  return (tecent1 / sqrt(tecent2 * tecent3));
}
