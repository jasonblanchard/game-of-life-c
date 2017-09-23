#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "cli_renderer.h"
#include "csv_parser.h"
#include "ticker.h"

int main(int argc, char *argv[]) {
  printf("\n");

  char flag;
  char *seed_file_name;
  int rate = 1000 * 1000;
  int should_clear = 0;
  int generation = 0;
  int show_stats = 0;
  int max_generation = 0;
  int height = 0;
  int width = 0;
  CsvParserNode *node;

  while((flag = getopt(argc, argv, "f:r:csm:")) != EOF) {
    switch(flag) {
      case 'f':
        seed_file_name = optarg;
        break;
      case 'r':
        rate = atof(optarg) * 1000;
        break;
      case 'c':
        should_clear = 1;
        break;
      case 's':
        show_stats = 1;
        break;
      case 'm':
        max_generation = atoi(optarg);
        break;
      default:
        fprintf(stderr, "%s\n", "That's not a valid argument");
    }
  }

  if (seed_file_name) {
    node = create_node();
    parse_seed_csv_rows(seed_file_name, node, &height, &width);
  }

  int board[height][width];

  if (seed_file_name) populate_matrix_from_node(node, height, width, board);

  while (1) {
    if (max_generation && generation >= max_generation + 1) break;
    should_clear ? system("clear") : printf("\n");
    cli_render_board(height, width, board);
    if (show_stats) {
      printf("\n");
      printf("\n");
      cli_render_stats(generation, height, width, board);
    }
    tick(height, width, board);
    printf("\n");
    generation++;
    usleep(rate);
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
