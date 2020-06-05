#ifndef TOP_DOWN_TASKS_ALGORITHM_H
#define TOP_DOWN_TASKS_ALGORITHM_H


#include "IFlowAccumulationAlgorithm.h"
#include "InletNumberCalculator.h"
#include <omp.h>


class TopDownTasksAlgorithm: public IFlowAccumulationAlgorithm
{
  public:
    FlowAccumulationMatrix execute(const FlowDirectionMatrix& directionMatrix);
};


#endif
