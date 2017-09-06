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
    // function that populates a linked list of all the lines and figures out the width and height of the board
    CsvParserNode node;
    int height = 0;
    parseSeedCsvRows(seedFileName, &node, &height);
    printf("%i\n", height);
    // printf("%s\n", node.next->row);

    CsvParserNode *tmpNode = &node;
    while(tmpNode->next != NULL) {
      printf("%s", tmpNode->row);
      tmpNode = tmpNode->next;
    }

    // function that constructs the multidimensional array from the linked list

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
