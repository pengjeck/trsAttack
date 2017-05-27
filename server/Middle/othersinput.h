#ifndef OTHERSINPUT_H
#define OTHERSINPUT_H

#include "middle_method.h"
// #include "io.h"

class OthersInput : public Middle_Method{
public:
  OthersInput(Parameter *parameter);

  //nonprofile�����µ��м�ֵ���㷽��
  vector<int> NoneProfileMiddle(QString plain_s, int SNum);

  //profile�����µ��м�ֵ���㷽��
  int ProfileMiddle(QString plain_s, int correctkey, int SNum);

private:
  Parameter *p;
  // IO *io;
};

#endif // OTHERSINPUT_H
