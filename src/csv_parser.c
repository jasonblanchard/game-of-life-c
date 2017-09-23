#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv_parser.h"

CsvParserNode* create_node() {
  CsvParserNode *p = (CsvParserNode*)malloc(sizeof(CsvParserNode));
  if (p != NULL) {
    p->next = NULL;
  }
  return p;
}

int count_delimited_values(char *string, const char delimiter) {
  int count = 1;

  while(*string) {
    if (*string == delimiter) {
      count++;
    }
    string++;
  }

  return count;
}

CsvParserNode * parse_seed_csv_rows(char *fileName, int *height, int *width) {
  *height = 0;
  char *string_buffer = NULL;
  CsvParserNode *head = create_node();
  CsvParserNode *node_buffer = head;
  FILE *file_pointer = fopen(fileName, "r");
  size_t buffer_length = 0;

  if (file_pointer == NULL) {
    fprintf(stderr, "Cannot open file\n");
    exit(1);
  }

  while((getline(&string_buffer, &buffer_length, file_pointer)) != -1) {
    if (*height == 0) *width = count_delimited_values(string_buffer, ',');

    CsvParserNode *tmp_node = *height == 0 ? head : create_node();
    tmp_node->row = malloc(strlen(string_buffer) + 1);
    strcpy(tmp_node->row, string_buffer);
    node_buffer->next = tmp_node;
    node_buffer = tmp_node;

    *height += 1;
  }

  free(string_buffer);
  fclose(file_pointer);
  return head;
}

void free_list(CsvParserNode *head) {
  CsvParserNode *tmp;

  while(head != NULL) {
    tmp = head;
    head = head->next;
    free(tmp->row);
    free(tmp);
  }
}

void populate_matrix_from_node(CsvParserNode *head, int height, int width, int matrix[][width]) {
  int i;
  int j;
  char *token, *str;
  CsvParserNode *tmp_node = head;

  for (i = 0; i < height; i++) {
    str = tmp_node->row;

    for (j = 0; j < width; j++) {
      token = strsep(&str, ",");
      matrix[i][j] = atoi(token);
    }
    tmp_node = tmp_node->next;
  }

  free_list(head);
}
