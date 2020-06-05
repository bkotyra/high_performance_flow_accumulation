#include "TopDownSequentialAlgorithm.h"


FlowAccumulationMatrix TopDownSequentialAlgorithm::execute(const FlowDirectionMatrix& directionMatrix)
{
  const char cellCompleted = -1;

  const int matrixHeight = directionMatrix.height;
  const int matrixWidth = directionMatrix.width;

  InletNumberMatrix inletNumberMatrix = InletNumberCalculator::calculate(directionMatrix);
  FlowAccumulationMatrix accumulationMatrix(matrixHeight, matrixWidth, 0);

  for (int row = 1; row <= matrixHeight; ++row)
  {
    for (int col = 1; col <= matrixWidth; ++col)
    {
      if ((inletNumberMatrix.value[row][col] == 0) && (directionMatrix.value[row][col] != DIRECTION_NONE))
      {
        int pathRow = row;
        int pathCol = col;

        do
        {
          const unsigned int pathLoad = accumulationMatrix.value[pathRow][pathCol] + 1;
          inletNumberMatrix.value[pathRow][pathCol] = cellCompleted;

          switch (directionMatrix.value[pathRow][pathCol])
          {
            case DIRECTION_RIGHT:                 ++pathCol; break;
            case DIRECTION_DOWN_RIGHT: ++pathRow; ++pathCol; break;
            case DIRECTION_DOWN:       ++pathRow;            break;
            case DIRECTION_DOWN_LEFT:  ++pathRow; --pathCol; break;
            case DIRECTION_LEFT:                  --pathCol; break;
            case DIRECTION_UP_LEFT:    --pathRow; --pathCol; break;
            case DIRECTION_UP:         --pathRow;            break;
            case DIRECTION_UP_RIGHT:   --pathRow; ++pathCol; break;
          }

          accumulationMatrix.value[pathRow][pathCol] += pathLoad;
          inletNumberMatrix.value[pathRow][pathCol]--;
        }
        while ((inletNumberMatrix.value[pathRow][pathCol] == 0) && (directionMatrix.value[pathRow][pathCol] != DIRECTION_NONE));
      }
    }
  }

  return accumulationMatrix;
}
