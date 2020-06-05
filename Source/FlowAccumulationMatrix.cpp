#include "FlowAccumulationMatrix.h"


FlowAccumulationMatrix::FlowAccumulationMatrix(int height, int width):
  FramedMatrix<unsigned int>(height, width, 0)
{
}


FlowAccumulationMatrix::FlowAccumulationMatrix(int height, int width, unsigned int fillValue):
  FramedMatrix<unsigned int>(height, width, 0, fillValue)
{
}
