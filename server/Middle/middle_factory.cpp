#include "middle_factory.h"

Middle_Factory::Middle_Factory()
{
}

Middle_Method * Middle_Factory::createMiddleMethod(Parameter *parameter)
{
    if(parameter->Algo=="AES")
        return new AES(parameter);
    else if(parameter->Algo=="SMS4")
        return new SMS4(parameter);
    else
        return new OthersInput(parameter);
}
