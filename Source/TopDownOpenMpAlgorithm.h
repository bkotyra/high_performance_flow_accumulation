#ifndef TOP_DOWN_OPENMP_ALGORITHM_H
#define TOP_DOWN_OPENMP_ALGORITHM_H


#include "IFlowAccumulationAlgorithm.h"
#include "InletNumberCalculator.h"
#include <omp.h>


class TopDownOpenMpAlgorithm: public IFlowAccumulationAlgorithm
{
  public:
    FlowAccumulationMatrix execute(const FlowDirectionMatrix& directionMatrix);
};


#endif
