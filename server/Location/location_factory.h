/*��λ��������ģʽ��
 * NICV
 * �������
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
