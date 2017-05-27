/*差分曲线方法类
 * */
#ifndef DIFFERENTIAL_METHOD_H
#define DIFFERENTIAL_METHOD_H

#include "location_method.h"
#include "dpa_method.h"


class Differential_Method : public Location_Method{
public:
  Differential_Method(Parameter *parameter);

  //初始化函数
  void init();

  //profile定位方法
  vector<double> ProfileLocation(QString plain, vector<double> power, int correctkey);

private:
  DPA_Method *dpa_method;
  Middle_Factory *MiddleF;
  Middle_Method *MiddleM;
  QString Model; //功耗泄露模型
  QString Algo; //加密算法
  int ByteNum; //定位字节序号
  QString Result_Path; //保存定位曲线路径
  // IO *FileIO;
};

#endif // DIFFERENTIAL_METHOD_H
