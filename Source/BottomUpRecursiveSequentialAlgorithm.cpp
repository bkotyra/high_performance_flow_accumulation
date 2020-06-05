#include "BottomUpRecursiveSequentialAlgorithm.h"


unsigned int BottomUpRecursiveSequentialAlgorithm::updateValue(const FlowDirectionMatrix& reversalDirectionMatrix, int row, int col, FlowAccumulationMatrix& accumulationMatrix)
{
  unsigned int accumulationSum = 0;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_RIGHT)
    accumulationSum += updateValue(reversalDirectionMatrix, row    , col + 1, accumulationMatrix) + 1;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_DOWN_RIGHT)
    accumulationSum += updateValue(reversalDirectionMatrix, row + 1, col + 1, accumulationMatrix) + 1;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_DOWN)
    accumulationSum += updateValue(reversalDirectionMatrix, row + 1, col    , accumulationMatrix) + 1;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_DOWN_LEFT)
    accumulationSum += updateValue(reversalDirectionMatrix, row + 1, col - 1, accumulationMatrix) + 1;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_LEFT)
    accumulationSum += updateValue(reversalDirectionMatrix, row    , col - 1, accumulationMatrix) + 1;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_UP_LEFT)
    accumulationSum += updateValue(reversalDirectionMatrix, row - 1, col - 1, accumulationMatrix) + 1;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_UP)
    accumulationSum += updateValue(reversalDirectionMatrix, row - 1, col    , accumulationMatrix) + 1;

  if (reversalDirectionMatrix.value[row][col] & DIRECTION_UP_RIGHT)
    accumulationSum += updateValue(reversalDirectionMatrix, row - 1, col + 1, accumulationMatrix) + 1;

  accumulationMatrix.value[row][col] = accumulationSum;

  return accumulationSum;
}


FlowAccumulationMatrix BottomUpRecursiveSequentialAlgorithm::execute(const FlowDirectionMatrix& directionMatrix)
{
  const int height = directionMatrix.height;
  const int width = directionMatrix.width;

  FlowDirectionMatrix reversalDirectionMatrix = FlowDirectionReverser::reverse(directionMatrix);
  FlowAccumulationMatrix accumulationMatrix(height, width);

  if (directionMatrix.value[1][1] & (DIRECTION_DOWN_LEFT | DIRECTION_LEFT | DIRECTION_UP_LEFT | DIRECTION_UP | DIRECTION_UP_RIGHT))
    updateValue(reversalDirectionMatrix, 1, 1, accumulationMatrix);

  if (directionMatrix.value[1][width] & (DIRECTION_UP_LEFT | DIRECTION_UP | DIRECTION_UP_RIGHT | DIRECTION_RIGHT | DIRECTION_DOWN_RIGHT))
    updateValue(reversalDirectionMatrix, 1, width, accumulationMatrix);

  if (directionMatrix.value[height][1] & (DIRECTION_DOWN_RIGHT | DIRECTION_DOWN | DIRECTION_DOWN_LEFT | DIRECTION_LEFT | DIRECTION_UP_LEFT))
    updateValue(reversalDirectionMatrix, height, 1, accumulationMatrix);

  if (directionMatrix.value[height][width] & (DIRECTION_UP_RIGHT | DIRECTION_RIGHT | DIRECTION_DOWN_RIGHT | DIRECTION_DOWN | DIRECTION_DOWN_LEFT))
    updateValue(reversalDirectionMatrix, height, width, accumulationMatrix);

  for (int col = 2; col <= width - 1; ++col)
  {
    if (directionMatrix.value[1][col] & (DIRECTION_UP_LEFT | DIRECTION_UP | DIRECTION_UP_RIGHT))
      updateValue(reversalDirectionMatrix, 1, col, accumulationMatrix);

    if (directionMatrix.value[height][col] & (DIRECTION_DOWN_LEFT | DIRECTION_DOWN | DIRECTION_DOWN_RIGHT))
      updateValue(reversalDirectionMatrix, height, col, accumulationMatrix);
  }

  for (int row = 2; row <= height - 1; ++row)
  {
    if (directionMatrix.value[row][1] & (DIRECTION_UP_LEFT | DIRECTION_LEFT | DIRECTION_DOWN_LEFT))
      updateValue(reversalDirectionMatrix, row, 1, accumulationMatrix);

    if (directionMatrix.value[row][width] & (DIRECTION_UP_RIGHT | DIRECTION_RIGHT | DIRECTION_DOWN_RIGHT))
      updateValue(reversalDirectionMatrix, row, width, accumulationMatrix);
  }

  for (int row = 1; row <= height; ++row)
  {
    for (int col = 1; col <= width; ++col)
    {
      if (directionMatrix.value[row][col] == DIRECTION_NONE)
        updateValue(reversalDirectionMatrix, row, col, accumulationMatrix);
    }
  }

  return accumulationMatrix;
}
