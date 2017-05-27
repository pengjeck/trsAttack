#ifndef PARAMETER_H
#define PARAMETER_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <vector>

using namespace std;

class Parameter{
public:
  QString analyser;                     //分析者姓名
  QString professional;                 //分析者职称
  QString organization;                 //分析者单位
  QString Analysis_method;              //分析方法
  QString Model;                        //功耗模型
  QString Loc;                          //定位方法
  QString Align;                        //对齐方法
  QString Algo;                         //目标加密算法
  QString Plain_Path;                   //明文路径
  QString Key_Path;                     //密钥路径
  QString Cipher_Path;                  //密文路径
  QString Power_Path;                   //功耗曲线路径
  QString Middle_Path;                  //中间值路径
  QString CorrectMiddle_Path;           //正确中间值路径
  QString Result_Path;                  //输出路径
  QString Analyse_Result_Path;          //分析输出路径
  QString Align_Result_Path;            //对齐输出路径
  QString Location_Result_Path;         //定位输出路径
  QString keytext;                      //子密钥
  QString TPlain_Path;                  //建模明文路径
  QString TKey_Path;                    //建模密钥路径
  QString TCipher_Path;                 //建模密文路径
  QString TPower_Path;                  //建模曲线路径
  QString Template_Path;                //模板路径
  QString TMiddle_Path;                 //模板中间值路径
  int NumofCurves;                      //分析所需曲线量
  int Start_Point;                      //起始点
  int TotalPoints;                      //总点数
  int OriginalPoints;                   //原始点数
  int Points;                           //预处理后点数
  int NumofSBox;                        //分析子密钥数量
  int ByteNum;                          //定位字节序号
  int HM00;                             //泄漏点前一状态
  int HM01;                             //泄漏点后一状态
  int SBoxLength;                       //2^k，k为子密钥比特数
  int IsLocationProfile;                //定位方法是否profile
  int IsProfile;                        //分析方法是否profile
  int IsBuildTemplate;                  //是否已经建立模板
  int TemplateNum;                      //模板个数
  int TaPointNum;                       //建模所用特征点数
  int SampleNum;                        //模板样本曲线数量
  int RangeOffset;                      //静态对齐扫描范围偏移量
  int IsValueBuild;                     //是否根据取值建模（共取值，汉明重两种）
  double AnalysisTime;                  //分析时间
  double MetricsTime;                   //计算指标时间
  double AlignTime;                     //对齐时间
  double LocationTime;                  //定位时间
  vector<QString> kbyte;                //分析候选密钥
  vector<int> findnum;                  //分析成功所需曲线量
  vector<double> refer_trace;          //静态对齐基准曲线
  vector<vector<int> > Template_Middle; //建模所需已知密钥中间值
};

#endif // PARAMETER_H
