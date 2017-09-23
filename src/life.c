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
  int generation = 0;
  int showStats = 0;
  int maxGeneration = 0;

  while((flag = getopt(argc, argv, "f:r:csm:")) != EOF) {
    switch(flag) {
      case 'f':
        seedFileName = optarg;
        break;
      case 'r':
        rate = atof(optarg) * 1000;
        break;
      case 'c':
        shouldClear = 1;
        break;
      case 's':
        showStats = 1;
        break;
      case 'm':
        maxGeneration = atoi(optarg);
        break;
      default:
        fprintf(stderr, "%s\n", "That's not a valid argument");
    }
  }

  if (seedFileName) {
    // TODO: Move these outside this block scope so that we can generalize the generation logic.
    CsvParserNode *node = createNode();
    int height = 0;
    int width = 0;

    parseSeedCsvRows(seedFileName, node, &height, &width);

    // TODO: Not working with non-square boards
    if (height != width) {
      fprintf(stderr, "%s\n", "Error: Only works with square game boards ¯_(ツ)_/¯");
      return 1;
    }

    int board[width][height];
    populateMatrixFromNode(node, width, height, board);

    while (1) {
      if (maxGeneration && generation >= maxGeneration + 1) break;
      shouldClear ? system("clear") : printf("\n");
      cliRender(width, height, board);
      if (showStats) {
        printf("\n");
        printf("\n");
        cliRenderStats(generation, width, height, board);
      }
      tick(width, height, board);
      printf("\n");
      generation++;
      usleep(rate);
    }
  }

  argc -= optind;
  argv -= optind;

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
