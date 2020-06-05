#ifndef FLOW_ACCUMULATION_MATRIX_H
#define FLOW_ACCUMULATION_MATRIX_H


#include "FramedMatrix.h"


struct FlowAccumulationMatrix: public FramedMatrix<unsigned int>
{
  public:
    FlowAccumulationMatrix(int height, int width);
    FlowAccumulationMatrix(int height, int width, unsigned int fillValue);
};


#endif
