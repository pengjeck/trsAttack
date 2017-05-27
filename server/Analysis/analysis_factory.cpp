#include "analysis_factory.h"

Analysis_factory::Analysis_factory(){
}

/**
 * 攻击方法
 * @param parameter
 * @return
 */
Analysis_Method *Analysis_factory::createAnalysisMethod(Parameter *parameter){

  if(parameter->Analysis_method == "DPA"){
    // 差分
    return new DPA_Method(parameter);
  }
  if(parameter->Analysis_method == "CPA"){
    // 相关性
    // return nullptr;
    return new CPA_Method(parameter);
  }
  if(parameter->Analysis_method == "MIA"){
    return nullptr;
//         return new MIA_Attack(parameter);
  }
  if(parameter->Analysis_method == "TA"){
    return nullptr;
//         return new TA_Method(parameter);
  }

  return nullptr;
}
