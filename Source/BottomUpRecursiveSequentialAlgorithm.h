#ifndef BOTTOM_UP_RECURSIVE_SEQUENTIAL_ALGORITHM_H
#define BOTTOM_UP_RECURSIVE_SEQUENTIAL_ALGORITHM_H


#include "IFlowAccumulationAlgorithm.h"
#include "FlowDirectionReverser.h"


class BottomUpRecursiveSequentialAlgorithm: public IFlowAccumulationAlgorithm
{
  private:
    unsigned int updateValue(const FlowDirectionMatrix& reversalDirectionMatrix, int row, int col, FlowAccumulationMatrix& accumulationMatrix);

  public:
    FlowAccumulationMatrix execute(const FlowDirectionMatrix& directionMatrix);
};


#endif
