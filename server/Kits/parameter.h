#ifndef PARAMETER_H
#define PARAMETER_H

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <vector>

using namespace std;

class Parameter{
public:
  QString analyser;                     //����������
  QString professional;                 //������ְ��
  QString organization;                 //�����ߵ�λ
  QString Analysis_method;              //��������
  QString Model;                        //����ģ��
  QString Loc;                          //��λ����
  QString Align;                        //���뷽��
  QString Algo;                         //Ŀ������㷨
  QString Plain_Path;                   //����·��
  QString Key_Path;                     //��Կ·��
  QString Cipher_Path;                  //����·��
  QString Power_Path;                   //��������·��
  QString Middle_Path;                  //�м�ֵ·��
  QString CorrectMiddle_Path;           //��ȷ�м�ֵ·��
  QString Result_Path;                  //���·��
  QString Analyse_Result_Path;          //�������·��
  QString Align_Result_Path;            //�������·��
  QString Location_Result_Path;         //��λ���·��
  QString keytext;                      //����Կ
  QString TPlain_Path;                  //��ģ����·��
  QString TKey_Path;                    //��ģ��Կ·��
  QString TCipher_Path;                 //��ģ����·��
  QString TPower_Path;                  //��ģ����·��
  QString Template_Path;                //ģ��·��
  QString TMiddle_Path;                 //ģ���м�ֵ·��
  int NumofCurves;                      //��������������
  int Start_Point;                      //��ʼ��
  int TotalPoints;                      //�ܵ���
  int OriginalPoints;                   //ԭʼ����
  int Points;                           //Ԥ��������
  int NumofSBox;                        //��������Կ����
  int ByteNum;                          //��λ�ֽ����
  int HM00;                             //й©��ǰһ״̬
  int HM01;                             //й©���һ״̬
  int SBoxLength;                       //2^k��kΪ����Կ������
  int IsLocationProfile;                //��λ�����Ƿ�profile
  int IsProfile;                        //���������Ƿ�profile
  int IsBuildTemplate;                  //�Ƿ��Ѿ�����ģ��
  int TemplateNum;                      //ģ�����
  int TaPointNum;                       //��ģ������������
  int SampleNum;                        //ģ��������������
  int RangeOffset;                      //��̬����ɨ�跶Χƫ����
  int IsValueBuild;                     //�Ƿ����ȡֵ��ģ����ȡֵ�����������֣�
  double AnalysisTime;                  //����ʱ��
  double MetricsTime;                   //����ָ��ʱ��
  double AlignTime;                     //����ʱ��
  double LocationTime;                  //��λʱ��
  vector<QString> kbyte;                //������ѡ��Կ
  vector<int> findnum;                  //�����ɹ�����������
  vector<double> refer_trace;          //��̬�����׼����
  vector<vector<int> > Template_Middle; //��ģ������֪��Կ�м�ֵ
};

#endif // PARAMETER_H
