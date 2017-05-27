/*�����㷨����ģʽ��
 * ��̬����
 * ��̬ʱ�����
 * ��λ���
 * ���ٸ���Ҷ
*/
#ifndef ALIGNMENT_FACTORY_H
#define ALIGNMENT_FACTORY_H

#include "alignment_method.h"
#include "fft_method.h"
#include "poc.h"
#include "dtw.h"
#include "staticalignment_method.h"

class Alignment_Factory{
public:
  Alignment_Factory();

  Alignment_Method *createAlignmentMethod(Parameter *parameter);
};

#endif // ALIGNMENT_FACTORY_H
