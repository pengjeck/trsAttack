/*���뷽������
 * */
#ifndef ALIGNMENT_METHOD_H
#define ALIGNMENT_METHOD_H
#include <math.h>
#include <vector>
#include "parameter.h"

using namespace std;

class Alignment_Method{
public:
  Alignment_Method();

  //���뺯��
  virtual vector<double> Align(vector<double> samples){
    vector<double> temp;
    return temp;
  }
};

#endif // ALIGNMENT_METHOD_H
