/*分析方法工厂模式类
 * DPA
 * CPA
 * MIA
 * TA
 * */
#ifndef ANALYSIS_FACTORY_H
#define ANALYSIS_FACTORY_H

#include "analysis_method.h"
#include "cpa_method.h"
#include "dpa_method.h"
// #include "ta_method.h"
// #include "mia_attack.h"

class Analysis_factory{
public:
  Analysis_factory();

  Analysis_Method *createAnalysisMethod(Parameter *parameter);
};

#endif // ANALYSIS_FACTORY_H
