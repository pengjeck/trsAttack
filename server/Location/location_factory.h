/*定位方法工厂模式类
 * NICV
 * 差分曲线
 * */
#ifndef LOCATION_FACTORY_H
#define LOCATION_FACTORY_H

#include "location_method.h"
#include "differential_method.h"
#include "nicv_method.h"


class Location_Factory{
public:
  Location_Factory();

  Location_Method *createLocationMethod(Parameter *parameter);
};

#endif // LOCATION_FACTORY_H
