typedef struct CsvParserNode {
  char *row;
  struct CsvParserNode *next;
} CsvParserNode;

void parse_seed_csv_rows(char *fileName, CsvParserNode *node, int *height, int *width);

void populate_matrix_from_node(CsvParserNode *node, int height, int width, int matrix[][width]);

CsvParserNode* create_node();
