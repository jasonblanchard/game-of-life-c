typedef struct CsvParserNode {
  char *row;
  struct CsvParserNode *next;
} CsvParserNode;

void parseSeedCsvRows(char *fileName, CsvParserNode *node, int *height, int *width);

void populateMatrixFromNode(CsvParserNode *node, int width, int height, int matrix[][height]);
