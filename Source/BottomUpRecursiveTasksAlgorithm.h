#ifndef BOTTOM_UP_RECURSIVE_TASKS_ALGORITHM_H
#define BOTTOM_UP_RECURSIVE_TASKS_ALGORITHM_H


#include "IFlowAccumulationAlgorithm.h"
#include "FlowDirectionReverser.h"
#include <omp.h>


class BottomUpRecursiveTasksAlgorithm: public IFlowAccumulationAlgorithm
{
  private:
    const int parallelRecursionLimit;

    unsigned int updateValueSequential(const FlowDirectionMatrix& reversalDirectionMatrix, int row, int col, FlowAccumulationMatrix& accumulationMatrix);
    unsigned int updateValueParallel(const FlowDirectionMatrix& reversalDirectionMatrix, int row, int col, FlowAccumulationMatrix& accumulationMatrix, int recursionLevel);

  public:
    BottomUpRecursiveTasksAlgorithm(int parallelRecursionLimit);

    FlowAccumulationMatrix execute(const FlowDirectionMatrix& directionMatrix);
};


#endif
