#include "InletNumberCalculator.h"


InletNumberMatrix InletNumberCalculator::calculate(const FlowDirectionMatrix& directionMatrix)
{
  const int height = directionMatrix.height;
  const int width = directionMatrix.width;

  InletNumberMatrix inletNumberMatrix(height, width);

  for (int row = 1; row <= height; ++row)
  {
    for (int col = 1; col <= width; ++col)
    {
      inletNumberMatrix.value[row][col] = ((directionMatrix.value[row    ][col - 1] & DIRECTION_RIGHT)) +
                                          ((directionMatrix.value[row - 1][col - 1] & DIRECTION_DOWN_RIGHT) >> 1) +
                                          ((directionMatrix.value[row - 1][col    ] & DIRECTION_DOWN) >> 2) +
                                          ((directionMatrix.value[row - 1][col + 1] & DIRECTION_DOWN_LEFT) >> 3) +
                                          ((directionMatrix.value[row    ][col + 1] & DIRECTION_LEFT) >> 4) +
                                          ((directionMatrix.value[row + 1][col + 1] & DIRECTION_UP_LEFT) >> 5) +
                                          ((directionMatrix.value[row + 1][col    ] & DIRECTION_UP) >> 6) +
                                          ((directionMatrix.value[row + 1][col - 1] & DIRECTION_UP_RIGHT) >> 7);
    }
  }

  return inletNumberMatrix;
}


InletNumberMatrix InletNumberCalculator::calculate(const FlowDirectionMatrix& directionMatrix, char ridgeValue)
{
  const int height = directionMatrix.height;
  const int width = directionMatrix.width;

  InletNumberMatrix inletNumberMatrix(height, width);

  for (int row = 1; row <= height; ++row)
  {
    for (int col = 1; col <= width; ++col)
    {
      inletNumberMatrix.value[row][col] = ((directionMatrix.value[row    ][col - 1] & DIRECTION_RIGHT)) +
                                          ((directionMatrix.value[row - 1][col - 1] & DIRECTION_DOWN_RIGHT) >> 1) +
                                          ((directionMatrix.value[row - 1][col    ] & DIRECTION_DOWN) >> 2) +
                                          ((directionMatrix.value[row - 1][col + 1] & DIRECTION_DOWN_LEFT) >> 3) +
                                          ((directionMatrix.value[row    ][col + 1] & DIRECTION_LEFT) >> 4) +
                                          ((directionMatrix.value[row + 1][col + 1] & DIRECTION_UP_LEFT) >> 5) +
                                          ((directionMatrix.value[row + 1][col    ] & DIRECTION_UP) >> 6) +
                                          ((directionMatrix.value[row + 1][col - 1] & DIRECTION_UP_RIGHT) >> 7);

      if (inletNumberMatrix.value[row][col] == 0)
      {
        inletNumberMatrix.value[row][col] = ridgeValue;
      }
    }
  }

  return inletNumberMatrix;
}


InletNumberMatrix InletNumberCalculator::calculateParallel(const FlowDirectionMatrix& directionMatrix)
{
  const int height = directionMatrix.height;
  const int width = directionMatrix.width;

  InletNumberMatrix inletNumberMatrix(height, width);

  #pragma omp parallel
  {
    #pragma omp for
    for (int row = 1; row <= height; ++row)
    {
      for (int col = 1; col <= width; ++col)
      {
        inletNumberMatrix.value[row][col] = ((directionMatrix.value[row    ][col - 1] & DIRECTION_RIGHT)) +
                                            ((directionMatrix.value[row - 1][col - 1] & DIRECTION_DOWN_RIGHT) >> 1) +
                                            ((directionMatrix.value[row - 1][col    ] & DIRECTION_DOWN) >> 2) +
                                            ((directionMatrix.value[row - 1][col + 1] & DIRECTION_DOWN_LEFT) >> 3) +
                                            ((directionMatrix.value[row    ][col + 1] & DIRECTION_LEFT) >> 4) +
                                            ((directionMatrix.value[row + 1][col + 1] & DIRECTION_UP_LEFT) >> 5) +
                                            ((directionMatrix.value[row + 1][col    ] & DIRECTION_UP) >> 6) +
                                            ((directionMatrix.value[row + 1][col - 1] & DIRECTION_UP_RIGHT) >> 7);
      }
    }
  }

  return inletNumberMatrix;
}


InletNumberMatrix InletNumberCalculator::calculateParallel(const FlowDirectionMatrix& directionMatrix, char ridgeValue)
{
  const int height = directionMatrix.height;
  const int width = directionMatrix.width;

  InletNumberMatrix inletNumberMatrix(height, width);

  #pragma omp parallel
  {
    #pragma omp for
    for (int row = 1; row <= height; ++row)
    {
      for (int col = 1; col <= width; ++col)
      {
        inletNumberMatrix.value[row][col] = ((directionMatrix.value[row    ][col - 1] & DIRECTION_RIGHT)) +
                                            ((directionMatrix.value[row - 1][col - 1] & DIRECTION_DOWN_RIGHT) >> 1) +
                                            ((directionMatrix.value[row - 1][col    ] & DIRECTION_DOWN) >> 2) +
                                            ((directionMatrix.value[row - 1][col + 1] & DIRECTION_DOWN_LEFT) >> 3) +
                                            ((directionMatrix.value[row    ][col + 1] & DIRECTION_LEFT) >> 4) +
                                            ((directionMatrix.value[row + 1][col + 1] & DIRECTION_UP_LEFT) >> 5) +
                                            ((directionMatrix.value[row + 1][col    ] & DIRECTION_UP) >> 6) +
                                            ((directionMatrix.value[row + 1][col - 1] & DIRECTION_UP_RIGHT) >> 7);

        if (inletNumberMatrix.value[row][col] == 0)
        {
          inletNumberMatrix.value[row][col] = ridgeValue;
        }
      }
    }
  }

  return inletNumberMatrix;
}
