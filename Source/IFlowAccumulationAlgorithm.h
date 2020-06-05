#ifndef I_FLOW_ACCUMULATION_ALGORITHM_H
#define I_FLOW_ACCUMULATION_ALGORITHM_H


#include "FlowDirectionMatrix.h"
#include "FlowAccumulationMatrix.h"


class IFlowAccumulationAlgorithm
{
  public:
    virtual ~IFlowAccumulationAlgorithm() = 0;
    virtual FlowAccumulationMatrix execute(const FlowDirectionMatrix& directionMatrix) = 0;
};


#endif
