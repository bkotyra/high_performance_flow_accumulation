#include "TopDownTasksAlgorithm.h"


FlowAccumulationMatrix TopDownTasksAlgorithm::execute(const FlowDirectionMatrix& directionMatrix)
{
  const char cellCompleted = -1;
  const char cellRidge = -2;

  const int matrixHeight = directionMatrix.height;
  const int matrixWidth = directionMatrix.width;

  InletNumberMatrix inletNumberMatrix = InletNumberCalculator::calculateParallel(directionMatrix, cellRidge);
  FlowAccumulationMatrix accumulationMatrix(matrixHeight, matrixWidth, 0);

  #pragma omp parallel
  {
    #pragma omp for schedule(dynamic)
    for (int row = 1; row <= matrixHeight; ++row)
    {
      for (int col = 1; col <= matrixWidth; ++col)
      {
        if ((inletNumberMatrix.value[row][col] == cellRidge) && (directionMatrix.value[row][col] != DIRECTION_NONE))
        {
          #pragma omp task
          {
            int pathRow = row;
            int pathCol = col;
            char pathInletNumber;

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

              #pragma omp atomic update
              accumulationMatrix.value[pathRow][pathCol] += pathLoad;

              #pragma omp atomic capture
              pathInletNumber = --inletNumberMatrix.value[pathRow][pathCol];
            }
            while ((pathInletNumber == 0) && (directionMatrix.value[pathRow][pathCol] != DIRECTION_NONE));
          }
        }
      }
    }
  }

  return accumulationMatrix;
}
