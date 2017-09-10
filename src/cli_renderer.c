#include <stdio.h>

void cli_render(int width, int height, int board[][height]) {
  int x;
  int y;

  for (x = 0; x < width; x++) {
    if (x > 0) printf("\n");
    for (y = 0; y < height; y++) {
      printf(" %i ", board[x][y]);
    }
  }
}

// void cli_render(int height, int width, int *board) {
//   int x;
//   int y;
//
//   for (x = 0; x < height; x++) {
//     printf("\n");
//     for (y = 0; y < width; y++) {
//       printf("%d ", *((board + x * width) + y));
//     }
//   }
// }
