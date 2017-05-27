#include "location_factory.h"

/**
 * 定位
 */
Location_Factory::Location_Factory(){
}

Location_Method *Location_Factory::createLocationMethod(Parameter *parameter){

  if(parameter->Loc == "NICV"){
    return new NICV_Method(parameter);
  }
  if(parameter->Loc == "DifferentialTrace"){
    return new Differential_Method(parameter);
  }
}
