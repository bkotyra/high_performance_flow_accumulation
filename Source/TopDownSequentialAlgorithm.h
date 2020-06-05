#ifndef TOP_DOWN_SEQUENTIAL_ALGORITHM_H
#define TOP_DOWN_SEQUENTIAL_ALGORITHM_H


#include "IFlowAccumulationAlgorithm.h"
#include "InletNumberCalculator.h"


class TopDownSequentialAlgorithm: public IFlowAccumulationAlgorithm
{
  public:
    FlowAccumulationMatrix execute(const FlowDirectionMatrix& directionMatrix);
};


#endif
