#include <stdio.h>

void cli_render_board(int height, int width, int board[][width], int graphicsMode) {
  int x;
  int y;

  for (x = 0; x < height; x++) {
    if (x > 0) printf("\n");
    for (y = 0; y < width; y++) {
      if (graphicsMode) {
        board[x][y] > 0 ? printf("+") : printf("  ");
      } else {
        printf(" %i ", board[x][y]);
      }
    }
  }
}

void cli_render_stats(int numGeneration, int height, int width, int board[][width]) {
  int x;
  int y;
  int numAlive = 0;
  int oldestCellAge = 0;

  for (x = 0; x < height; x++) {
    for (y = 0; y < width; y++) {
      if (board[x][y] > 0) numAlive++;
      if (board[x][y] > oldestCellAge) oldestCellAge = board[x][y];
    }
  }

  printf("Generation: %i Alive Cells: %i Oldest Cell Age: %i", numGeneration, numAlive, oldestCellAge);
}
