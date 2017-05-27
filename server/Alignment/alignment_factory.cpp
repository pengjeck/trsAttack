#include "alignment_factory.h"

/**
 * 对齐方法
 */
Alignment_Factory::Alignment_Factory(){
}

Alignment_Method *Alignment_Factory::createAlignmentMethod(Parameter *parameter){
  if(parameter->Align == "StaticAlignment"){
    return new StaticAlignment_Method(parameter);
  }
  if(parameter->Align == "FFT")
    return new FFT_Method(parameter);
  if(parameter->Align == "DTW")
    return new dtw(parameter);
  if(parameter->Align == "POC")
    return new POC(parameter);

  return 0;
}
