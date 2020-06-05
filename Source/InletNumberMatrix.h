#ifndef INLET_NUMBER_MATRIX_H
#define INLET_NUMBER_MATRIX_H


#include "FramedMatrix.h"


struct InletNumberMatrix: public FramedMatrix<char>
{
  public:
    InletNumberMatrix(int height, int width);
};


#endif
