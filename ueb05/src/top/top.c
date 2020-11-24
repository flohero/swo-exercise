#include "./top.h"
#include <stdlib.h>
#include <stdio.h>
#include "../adt/utils.h"

#define log_error(type) log_error((type), __func__, __LINE__);

#define exit_on_mem_error(expr) exit_on_mem_error((expr), __func__, __LINE__)


typedef struct visited_node {
  char *value;
  size_t incoming_edges;
  bool visited;
} visited_node;

static size_t recalculate_visited_node(graph_matrix *graph, visited_node *visited_nodes);

/**
 * Prints the graph topological sorted
 */
void graph_matrix_topological_sort(graph_matrix *graph) {
  visited_node *visited_nodes = malloc(graph->size * sizeof(visited_node));
  exit_on_mem_error(visited_nodes == NULL);
  // topological array
  for (size_t i = 0; i < graph->size; i++) {
    bool is_empty = graph->nodes[i].value == NULL;
    visited_nodes[i].visited = is_empty;
    // This node is empty and shouldn't be used
    if (is_empty) {
      continue;
    }
    visited_nodes[i].value = graph->nodes[i].value;
    visited_nodes[i].incoming_edges = 0;
    for (size_t j = 0; j < graph->size; j++) {
      bool edge_exists = graph->edges[j + i * graph->size];
      if (j == i && edge_exists) {
        log_error(cyclic_graph);
        free(visited_nodes);
        return;
      }
      // if there is an edge, incoming edges will be increased
      edge_exists
      && visited_nodes[i].incoming_edges++;
    }
  }
  bool cyclic = false;
  for (size_t nodes_left = graph->count; nodes_left != 0;
       nodes_left = recalculate_visited_node(graph, visited_nodes)) {
    if (cyclic) {
      log_error(cyclic_graph);
      free(visited_nodes);
      return;
    }
    cyclic = true;
    for (size_t i = 0; i < graph->size; i++) {
      if (visited_nodes[i].visited) {
        continue;
      }
      if (visited_nodes[i].incoming_edges == 0) {
        printf("\"%s\" ", visited_nodes[i].value);
        visited_nodes[i].visited = true;
        cyclic = false;
      }
    }
  }
  free(visited_nodes);
}

/**
 * Calculate how many incoming edges a node has
 * @returns the count of not visited nodes
 */
static size_t recalculate_visited_node(graph_matrix *graph, visited_node *visited_nodes) {
  size_t new_count = 0;
  for (size_t i = 0; i < graph->size; i++) {
    // This node is empty and shouldn't be used
    if (visited_nodes[i].visited) {
      continue;
    }
    new_count++;
    visited_nodes[i].incoming_edges = 0;
    for (size_t j = 0; j < graph->size; j++) {
      bool edge_exists = graph->edges[j + i * graph->size] && !visited_nodes[j].visited;
      // if there is an edge, incoming edges will be increased
      edge_exists
      && visited_nodes[i].incoming_edges++;
    }
  }
  return new_count;
}
