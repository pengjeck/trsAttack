#ifndef MIDDLE_FACTORY_H
#define MIDDLE_FACTORY_H

#include "middle_method.h"
#include "sms4.h"
#include "aes.h"
#include "othersinput.h"

class Middle_Factory{
public:
  Middle_Factory();

  Middle_Method *createMiddleMethod(Parameter *parameter);
};

#endif // MIDDLE_FACTORY_H
