#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv_parser.h"

CsvParserNode * create_node() {
  CsvParserNode *p = (CsvParserNode*)malloc(sizeof(CsvParserNode));
  if (p != NULL) {
    p->next = NULL;
  }
  return p;
}

void parseSeedCsvRows(char *fileName, CsvParserNode *node, int *height) {
  FILE *in = fopen(fileName, "r");
  char *buffer = NULL;
  size_t size = 0;
  CsvParserNode *nodeBuffer = node;
  *height = 0;

  while((getline(&buffer, &size, in)) != -1) {
    if (*height == 0) {
      nodeBuffer->row = malloc(strlen(buffer) + 1);
      strcpy(nodeBuffer->row, buffer);
    } else {
      CsvParserNode *tmpNode = create_node();
      tmpNode->row = malloc(strlen(buffer) + 1);
      strcpy(tmpNode->row, buffer);
      nodeBuffer->next = tmpNode;
      nodeBuffer = tmpNode;
    }
    *height += 1;
  }

  fclose(in);
}
