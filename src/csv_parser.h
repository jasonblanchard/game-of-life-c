typedef struct CsvParserNode {
  char *row;
  struct CsvParserNode *next;
} CsvParserNode;

void parseSeedCsvRows(char *fileName, CsvParserNode *node, int *height);
