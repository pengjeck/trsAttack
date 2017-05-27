/*定位方法父类
 * */
#ifndef LOCATION_METHOD_H
#define LOCATION_METHOD_H

#include "parameter.h"
#include "middle_factory.h"
#include <math.h>
#include <vector>

using namespace std;

class Location_Method{
public:
  Location_Method();

  //初始化虚函数
  virtual void init(){}

  //NoneProfie的定位方法
  virtual vector<double> NoneProfileLocation(QString plain, vector<double> power){
    vector<double> temp;
    return temp;
  }

  //Profile的定位方法
  virtual vector<double> ProfileLocation(QString plain, vector<double> power, int correctkey){
    vector<double> temp;
    return temp;
  }

};

#endif // LOCATION_METHOD_H
