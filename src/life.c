#include <stdio.h>
#include "cli_renderer.h"

int main() {
  printf("\n");
  printf("working\n");

  int board[6][6] = {
    {0, 0, 0, 1, 0, 0},
    {0, 0, 0, 2, 0, 0},
    {0, 0, 0, 3, 0, 0},
    {0, 0, 0, 4, 0, 0},
    {0, 0, 0, 5, 0, 0},
    {0, 0, 0, 6, 0, 0}
  };

  cli_render(6, 6, board);
  printf("\n");
  printf("\n");
}
