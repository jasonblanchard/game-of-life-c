#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cli_renderer.h"
#include "csv_parser.h"
#include "ticker.h"

int main(int argc, char *argv[]) {
  printf("\n");

  char flag;
  char *seedFileName;
  int rate = 1000 * 1000;
  int shouldClear = 0;

  while((flag = getopt(argc, argv, "s:r:c")) != EOF) {
    switch(flag) {
      case 's':
        seedFileName = optarg;
        break;
      case 'r':
        rate = atof(optarg) * 1000;
        break;
      case 'c':
        shouldClear = 1;
      default:
        fprintf(stderr, "%s\n", "That's not a valid argument");
    }
  }

  if (seedFileName) {
    CsvParserNode node;
    int height = 0;
    int width = 0;

    parseSeedCsvRows(seedFileName, &node, &height, &width);

    // TODO: Not working with non-square boards
    if (height != width) {
      fprintf(stderr, "%s\n", "Error: Only works with square game boards ¯_(ツ)_/¯");
      return 1;
    }

    int board[width][height];
    populateMatrixFromNode(&node, width, height, board);

    while (1) {
      shouldClear ? system("clear") : printf("\n");
      cli_render(width, height, board);
      tick(width, height, board);
      printf("\n");
      usleep(rate);
    }
  }

  argc -= optind;
  argv -= optind;

  // TODO: Stats: # generations, # alive, # dead, oldest cell

  // TODO: Populate a randmized board
  // int board[6][6] = {
  //   {0, 0, 0, 1, 0, 0 },
  //   {0, 0, 0, 2, 0, 0 },
  //   {0, 0, 0, 3, 0, 0 },
  //   {0, 0, 0, 4, 0, 0 },
  //   {0, 0, 0, 5, 0, 0 },
  //   {0, 0, 0, 6, 0, 0 }
  // };
  //
  // cli_render(6, 6, board);
  printf("\n");
  printf("\n");
}
