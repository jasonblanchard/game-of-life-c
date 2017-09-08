#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cli_renderer.h"
#include "csv_parser.h"

int main(int argc, char *argv[]) {
  printf("\n");
  printf("working\n");

  char flag;
  char *seedFileName;

  while((flag = getopt(argc, argv, "s:")) != EOF) {
    switch(flag) {
      case 's':
        seedFileName = optarg;
        break;
      default:
        fprintf(stderr, "%s\n", "That's not a valid argument");
    }
  }

  if (seedFileName) {
    CsvParserNode node;
    int height = 0;
    int width = 0;

    parseSeedCsvRows(seedFileName, &node, &height, &width);

    int board[width][height];
    populateMatrixFromNode(&node, width, height, board);

    cli_render(width, height, board);

    // TODO: Cleanup
  }

  argc -= optind;
  argv -= optind;

  // int board[6][6] = {
  //   {0, 0, 0, 1, 0, 0},
  //   {0, 0, 0, 2, 0, 0},
  //   {0, 0, 0, 3, 0, 0},
  //   {0, 0, 0, 4, 0, 0},
  //   {0, 0, 0, 5, 0, 0},
  //   {0, 0, 0, 6, 0, 0}
  // };

  // cli_render(6, 6, board);
  printf("\n");
  printf("\n");
}
