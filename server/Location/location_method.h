/*��λ��������
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

  //��ʼ���麯��
  virtual void init(){}

  //NoneProfie�Ķ�λ����
  virtual vector<double> NoneProfileLocation(QString plain, vector<double> power){
    vector<double> temp;
    return temp;
  }

  //Profile�Ķ�λ����
  virtual vector<double> ProfileLocation(QString plain, vector<double> power, int correctkey){
    vector<double> temp;
    return temp;
  }

};

#endif // LOCATION_METHOD_H
