#include "ticker.h"

int calculate_result(numNeighbors, currentValue) {
  // 4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
  if (currentValue == 0 && numNeighbors == 3) {
    return 1;
  }

  // 1. Any live cell with fewer than two live neighbours dies, as if caused by underpopulation.
  // 3. Any live cell with more than three live neighbours dies, as if by overpopulation.
  if (numNeighbors < 2 || numNeighbors > 3) {
    return 0;
  }

  // 2. Any live cell with two or three live neighbours lives on to the next generation.
  if (currentValue > 0 && (numNeighbors == 2 || numNeighbors == 3)) {
    return currentValue + 1;
  }

  // TODO: Can we find a defult if the above conditions aren't true? Are they mutually exclusive?
  return currentValue;
}

int calculate_num_neighbors(int i, int j, int height, int width, int board[][width]) {
  int numNeighbors = 0;

  if (i > 0) {
    if (j > 0 && board[i - 1][j - 1] > 0) numNeighbors++;
    if (board[i - 1][j] > 0) numNeighbors++;
    if (j < width && board[i - 1][j + 1] > 0) numNeighbors++;
  }

  if (j < width - 1) {
    if (board[i][j + 1] > 0) numNeighbors++;
    if (j > 0 && board[i][j - 1]) numNeighbors++;
  }

  if (i + 1 < height - 1) {
    if (j > 0 && board[i + 1][j - 1]) numNeighbors++;
    if (board[i + 1][j]) numNeighbors++;
    if (j < width && board[i + 1][j + 1]) numNeighbors++;
  }

  return numNeighbors;
}

void tick(int height, int width, int board[][width]) {
  int i;
  int j;
  int numNeighbors = 0;
  int buffer[height][width];

  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      numNeighbors = calculate_num_neighbors(i, j, height, width, board);
      buffer[i][j] = calculate_result(numNeighbors, board[i][j]);
    }
  }

  for (i = 0; i < height; i++) {
    for (j = 0; j < width; j++) {
      board[i][j] = buffer[i][j];
    }
  }
}
