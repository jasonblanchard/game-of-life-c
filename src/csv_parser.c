#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv_parser.h"

CsvParserNode* createNode() {
  CsvParserNode *p = (CsvParserNode*)malloc(sizeof(CsvParserNode));
  if (p != NULL) {
    p->next = NULL;
  }
  return p;
}

int countDelimitedValues(char *string, const char delimiter) {
  int count = 1;

  while(*string) {
    if (*string == delimiter) {
      count++;
    }
    string++;
  }

  return count;
}

void parseSeedCsvRows(char *fileName, CsvParserNode *node, int *height, int *width) {
  FILE *in = fopen(fileName, "r");
  char *buffer = NULL;
  size_t size = 0;
  CsvParserNode *nodeBuffer = node;
  *height = 0;

  while((getline(&buffer, &size, in)) != -1) {
    if (*height == 0) {
      *width = countDelimitedValues(buffer, ',');
      nodeBuffer->row = malloc(strlen(buffer) + 1);
      strcpy(nodeBuffer->row, buffer);
    } else {
      CsvParserNode *tmpNode = createNode();
      tmpNode->row = malloc(strlen(buffer) + 1);
      strcpy(tmpNode->row, buffer);
      nodeBuffer->next = tmpNode;
      nodeBuffer = tmpNode;
    }
    *height += 1;
  }

  fclose(in);
}

void populateMatrixFromNode(CsvParserNode *node, int width, int height, int matrix[][height]) {
  int i;
  int j;
  char *token, *str;
  CsvParserNode *tmpNode = node;

  for (i = 0; i < height; i++) {
    str = tmpNode->row;

    for (j = 0; j < width; j++) {
      token = strsep(&str, ",");
      matrix[i][j] = atoi(token);
    }
    tmpNode = tmpNode->next;
  }

  // TODO: Cleanup strings and nodes?
}
