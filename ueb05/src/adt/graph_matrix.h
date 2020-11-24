#ifndef SWO3_GRAPH_MATRIX_H
#define SWO3_GRAPH_MATRIX_H

#include <stdbool.h>

typedef struct node {
  char *value;
} node;

typedef struct graph_matrix {
  node *nodes;
  bool *edges; // Without payload we only want to know if an edge exists
  size_t count;
  size_t size;
} graph_matrix;

void graph_matrix_init(graph_matrix *graph);

void graph_matrix_add_node(graph_matrix *graph, const char *val);

void graph_matrix_add_edge(graph_matrix *graph, const char *source, const char *dest);

void graph_matrix_print(graph_matrix *graph);

void graph_matrix_remove_node(graph_matrix *graph, const char *value);

void graph_matrix_remove_edge(graph_matrix *graph, const char *source, const char *dest);

void graph_matrix_destroy(graph_matrix *graph);

void graph_matrix_topological_sort(graph_matrix *graph);

#endif //SWO3_GRAPH_MATRIX_H
