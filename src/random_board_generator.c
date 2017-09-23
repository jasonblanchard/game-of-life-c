#include <stdlib.h>
#include <time.h>

#include "random_board_generator.h"

void randomize(int height, int width, int board[][width]) {
  srand(time(NULL));
    for (int i = 0; i < height; i++) {
      for(int j = 0; j < width; j++) {
        board[i][j] = rand() % 2;
      }
  }
}
