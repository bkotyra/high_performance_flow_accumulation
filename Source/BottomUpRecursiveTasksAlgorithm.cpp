#include "BottomUpRecursiveTasksAlgorithm.h"


unsigned int BottomUpRecursiveTasksAlgorithm::updateValueSequential(const FlowDirectionMatrix& reversalDirectionMatrix, int row, int col, FlowAccumulationMatrix& accumulationMatrix)
{
  unsigned int accumulationSum = 0;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_RIGHT)
    accumulationSum += updateValueSequential(reversalDirectionMatrix, row    , col + 1, accumulationMatrix) + 1;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_DOWN_RIGHT)
    accumulationSum += updateValueSequential(reversalDirectionMatrix, row + 1, col + 1, accumulationMatrix) + 1;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_DOWN)
    accumulationSum += updateValueSequential(reversalDirectionMatrix, row + 1, col    , accumulationMatrix) + 1;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_DOWN_LEFT)
    accumulationSum += updateValueSequential(reversalDirectionMatrix, row + 1, col - 1, accumulationMatrix) + 1;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_LEFT)
    accumulationSum += updateValueSequential(reversalDirectionMatrix, row    , col - 1, accumulationMatrix) + 1;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_UP_LEFT)
    accumulationSum += updateValueSequential(reversalDirectionMatrix, row - 1, col - 1, accumulationMatrix) + 1;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_UP)
    accumulationSum += updateValueSequential(reversalDirectionMatrix, row - 1, col    , accumulationMatrix) + 1;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_UP_RIGHT)
    accumulationSum += updateValueSequential(reversalDirectionMatrix, row - 1, col + 1, accumulationMatrix) + 1;

  accumulationMatrix.value[row][col] = accumulationSum;

  return accumulationSum;
}


unsigned int BottomUpRecursiveTasksAlgorithm::updateValueParallel(const FlowDirectionMatrix& reversalDirectionMatrix, int row, int col, FlowAccumulationMatrix& accumulationMatrix, int recursionLevel)
{
  if (recursionLevel < parallelRecursionLimit)
  {
    unsigned int rightValue = 0;
    unsigned int downRightValue = 0;
    unsigned int downValue = 0;
    unsigned int downLeftValue = 0;
    unsigned int leftValue = 0;
    unsigned int upLeftValue = 0;
    unsigned int upValue = 0;
    unsigned int upRightValue = 0;

    if (reversalDirectionMatrix.value[row][col] & DIRECTION_RIGHT)
    {
      #pragma omp task shared(reversalDirectionMatrix, accumulationMatrix, rightValue)
      rightValue = updateValueParallel(reversalDirectionMatrix, row, col + 1, accumulationMatrix, recursionLevel + 1) + 1;
    }

    if (reversalDirectionMatrix.value[row][col] & DIRECTION_DOWN_RIGHT)
    {
      #pragma omp task shared(reversalDirectionMatrix, accumulationMatrix, downRightValue)
      downRightValue = updateValueParallel(reversalDirectionMatrix, row + 1, col + 1, accumulationMatrix, recursionLevel + 1) + 1;
    }

    if (reversalDirectionMatrix.value[row][col] & DIRECTION_DOWN)
    {
      #pragma omp task shared(reversalDirectionMatrix, accumulationMatrix, downValue)
      downValue = updateValueParallel(reversalDirectionMatrix, row + 1, col, accumulationMatrix, recursionLevel + 1) + 1;
    }

    if (reversalDirectionMatrix.value[row][col] & DIRECTION_DOWN_LEFT)
    {
      #pragma omp task shared(reversalDirectionMatrix, accumulationMatrix, downLeftValue)
      downLeftValue = updateValueParallel(reversalDirectionMatrix, row + 1, col - 1, accumulationMatrix, recursionLevel + 1) + 1;
    }

    if (reversalDirectionMatrix.value[row][col] & DIRECTION_LEFT)
    {
      #pragma omp task shared(reversalDirectionMatrix, accumulationMatrix, leftValue)
      leftValue = updateValueParallel(reversalDirectionMatrix, row, col - 1, accumulationMatrix, recursionLevel + 1) + 1;
    }

    if (reversalDirectionMatrix.value[row][col] & DIRECTION_UP_LEFT)
    {
      #pragma omp task shared(reversalDirectionMatrix, accumulationMatrix, upLeftValue)
      upLeftValue = updateValueParallel(reversalDirectionMatrix, row - 1, col - 1, accumulationMatrix, recursionLevel + 1) + 1;
    }

    if (reversalDirectionMatrix.value[row][col] & DIRECTION_UP)
    {
      #pragma omp task shared(reversalDirectionMatrix, accumulationMatrix, upValue)
      upValue = updateValueParallel(reversalDirectionMatrix, row - 1, col, accumulationMatrix, recursionLevel + 1) + 1;
    }

    if (reversalDirectionMatrix.value[row][col] & DIRECTION_UP_RIGHT)
    {
      #pragma omp task shared(reversalDirectionMatrix, accumulationMatrix, upRightValue)
      upRightValue = updateValueParallel(reversalDirectionMatrix, row - 1, col + 1, accumulationMatrix, recursionLevel + 1) + 1;
    }

    #pragma omp taskwait
    accumulationMatrix.value[row][col] = rightValue + downRightValue + downValue + downLeftValue + leftValue + upLeftValue + upValue + upRightValue;

    return accumulationMatrix.value[row][col];
  }

  else
  {
    return updateValueSequential(reversalDirectionMatrix, row, col, accumulationMatrix);
  }
}


BottomUpRecursiveTasksAlgorithm::BottomUpRecursiveTasksAlgorithm(int parallelRecursionLimit):
  parallelRecursionLimit(parallelRecursionLimit)
{
}


FlowAccumulationMatrix BottomUpRecursiveTasksAlgorithm::execute(const FlowDirectionMatrix& directionMatrix)
{
  const int height = directionMatrix.height;
  const int width = directionMatrix.width;

  FlowDirectionMatrix reversalDirectionMatrix = FlowDirectionReverser::reverseParallel(directionMatrix);
  FlowAccumulationMatrix accumulationMatrix(height, width);

  #pragma omp parallel
  {
    #pragma omp single nowait
    {
      if (directionMatrix.value[1][1] & (DIRECTION_DOWN_LEFT | DIRECTION_LEFT | DIRECTION_UP_LEFT | DIRECTION_UP | DIRECTION_UP_RIGHT))
        updateValueParallel(reversalDirectionMatrix, 1, 1, accumulationMatrix, 0);
    }

    #pragma omp single nowait
    {
      if (directionMatrix.value[1][width] & (DIRECTION_UP_LEFT | DIRECTION_UP | DIRECTION_UP_RIGHT | DIRECTION_RIGHT | DIRECTION_DOWN_RIGHT))
        updateValueParallel(reversalDirectionMatrix, 1, width, accumulationMatrix, 0);
    }

    #pragma omp single nowait
    {
      if (directionMatrix.value[height][1] & (DIRECTION_DOWN_RIGHT | DIRECTION_DOWN | DIRECTION_DOWN_LEFT | DIRECTION_LEFT | DIRECTION_UP_LEFT))
        updateValueParallel(reversalDirectionMatrix, height, 1, accumulationMatrix, 0);
    }

    #pragma omp single nowait
    {
      if (directionMatrix.value[height][width] & (DIRECTION_UP_RIGHT | DIRECTION_RIGHT | DIRECTION_DOWN_RIGHT | DIRECTION_DOWN | DIRECTION_DOWN_LEFT))
        updateValueParallel(reversalDirectionMatrix, height, width, accumulationMatrix, 0);
    }

    #pragma omp for schedule(dynamic) nowait
    for (int col = 2; col <= width - 1; ++col)
    {
      if (directionMatrix.value[1][col] & (DIRECTION_UP_LEFT | DIRECTION_UP | DIRECTION_UP_RIGHT))
        updateValueParallel(reversalDirectionMatrix, 1, col, accumulationMatrix, 0);
    }

    #pragma omp for schedule(dynamic) nowait
    for (int col = 2; col <= width - 1; ++col)
    {
      if (directionMatrix.value[height][col] & (DIRECTION_DOWN_LEFT | DIRECTION_DOWN | DIRECTION_DOWN_RIGHT))
        updateValueParallel(reversalDirectionMatrix, height, col, accumulationMatrix, 0);
    }

    #pragma omp for schedule(dynamic) nowait
    for (int row = 2; row <= height - 1; ++row)
    {
      if (directionMatrix.value[row][1] & (DIRECTION_UP_LEFT | DIRECTION_LEFT | DIRECTION_DOWN_LEFT))
        updateValueParallel(reversalDirectionMatrix, row, 1, accumulationMatrix, 0);
    }

    #pragma omp for schedule(dynamic) nowait
    for (int row = 2; row <= height - 1; ++row)
    {
      if (directionMatrix.value[row][width] & (DIRECTION_UP_RIGHT | DIRECTION_RIGHT | DIRECTION_DOWN_RIGHT))
        updateValueParallel(reversalDirectionMatrix, row, width, accumulationMatrix, 0);
    }

    #pragma omp for schedule(dynamic) nowait
    for (int row = 1; row <= height; ++row)
    {
      for (int col = 1; col <= width; ++col)
      {
        if (directionMatrix.value[row][col] == DIRECTION_NONE)
          updateValueParallel(reversalDirectionMatrix, row, col, accumulationMatrix, 0);
      }
    }
  }

  return accumulationMatrix;
}
