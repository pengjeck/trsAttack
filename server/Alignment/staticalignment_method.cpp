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
 * refer_trace：基准曲线，为攻击对应的曲线区间
 * misalign_trace:用于对齐的曲线,扫描该曲线上与基准曲线匹配的曲线区间
 * start:扫描曲线区间起点
 * end:扫描曲线区间终点
 */
vector<double> StaticAlignment_Method::Align(vector<double> samples){
  vector<double> misalign_trace = samples;
  vector<double> align_trace;
  align_trace.resize(this->base_trace.size()); //对齐后曲线
  vector<double> trace_fragment;
  trace_fragment.resize(this->base_trace.size()); //用于计算相关性的曲线区间
  int startindex_of_maxCorrelation = 0; //相关性最高的曲线区间起点
  double maxCorrelation = 0; //相关性极值
  double correlation_vector[end - start]; //存储所有相关性系数，方便查看
  for(int i = start; i < end; i++){
    if((i + this->base_trace.size()) > misalign_trace.size() - 1) break; //超出曲线长度
    //取出曲线区间
    for(int j = 0; j < this->base_trace.size(); j++){
      trace_fragment[j] = misalign_trace[j + i];
    }
    //计算相关系数
    double correlation = Cal_Correlation(this->base_trace,
                                         trace_fragment,
                                         this->base_trace.size());
    correlation_vector[i - start] = correlation;

    if(maxCorrelation < correlation){
      maxCorrelation = correlation;
      startindex_of_maxCorrelation = i;
    }

  }

  //取出相关性最大的匹配段
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
