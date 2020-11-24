#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "graph_matrix.h"
#include "utils.h"

#define log_error(type) log_error((type), __func__, __LINE__);
#define exit_on_mem_error(expr) exit_on_mem_error((expr), __func__, __LINE__)

#define MULT_FACTOR 2

typedef struct visited_node {
  char *value;
  size_t incoming_edges;
  bool visited;
} visited_node;

static size_t get_next_empty_index(const graph_matrix *graph);

static void set_next_size(graph_matrix *graph);

static void expand_graph(graph_matrix *graph);

static size_t get_position_of_node(graph_matrix *graph, const char *value);

static size_t recalculate_visited_node(graph_matrix *graph, visited_node *visited_nodes);

/**
 * Initializes the graph
 */
void graph_matrix_init(graph_matrix *graph) {
  if (graph == NULL) {
    log_error(null_pointer);
    return;
  }
  graph->count = 0;
  graph->size = 1;
  set_next_size(graph);
  graph->nodes = calloc(graph->size, sizeof(node));
  graph->edges = calloc(graph->size * graph->size, sizeof(bool));
  exit_on_mem_error(graph->edges == NULL || graph->nodes == NULL);
}

/**
 * Copies the string and inserts the copy,
 * so the string in the graph doesn't get changed.
 */
void graph_matrix_add_node(graph_matrix *graph, const char *val) {
  if (graph == NULL || val == NULL) {
    log_error(null_pointer);
    return;
  }
  if (get_position_of_node(graph, val) != graph->size) {
    log_error(node_already_exists);
    return;
  }
  size_t empty_index = get_next_empty_index(graph);
  if (empty_index == graph->size) {
    expand_graph(graph);
  }
  char *cpy = malloc((strlen(val) + 1) * sizeof(char));
  exit_on_mem_error(cpy == NULL);
  strcpy(cpy, val);
  graph->nodes[empty_index].value = cpy;
  graph->count++;
}

/**
 * Add an edge to the edge matrix
 * @param source where the edge starts
 * @param dest where it points to
 */
void graph_matrix_add_edge(graph_matrix *graph, const char *source, const char *dest) {
  if (graph == NULL || source == NULL || dest == NULL) {
    log_error(null_pointer);
    return;
  }
  size_t source_pos = get_position_of_node(graph, source);
  size_t dest_pos = get_position_of_node(graph, dest);

  if (source_pos == graph->size || dest_pos == graph->size) {
    log_error(node_doesnt_exist);
    return;
  }
  graph->edges[source_pos + dest_pos * graph->size] = true;
}

/**
 * Simple print of the graph
 */
void graph_matrix_print(graph_matrix *graph) {
  if (graph == NULL) {
    log_error(null_pointer);
    return;
  }
  for (size_t i = 0; i < graph->size; i++) {
    if (graph->nodes[i].value == NULL) {
      continue;
    }
    printf("%s: ", graph->nodes[i].value);
    for (size_t j = 0; j < graph->size; j++) {
      if (graph->edges[j * graph->size + i]) {
        printf("\"%s\" ", graph->nodes[j].value);
      }
    }
    printf("\n");
  }
}

/**
 * Removes a node and its incoming and outgoing edges
 */
void graph_matrix_remove_node(graph_matrix *graph, const char *value) {
  if (graph == NULL || value == NULL) {
    log_error(null_pointer);
    return;
  }
  size_t pos = get_position_of_node(graph, value);
  if (pos == graph->size) {
    log_error(node_doesnt_exist);
  }
  for (size_t i = 0; i < graph->size; i++) {
    // Remove incoming edges
    graph->edges[pos * graph->size + i] = false;
    // Remove outgoing edges
    graph->edges[i * graph->size + pos] = false;
  }
  free(graph->nodes[pos].value);
  graph->nodes[pos].value = NULL;
  graph->count--;
}

/**
 * Remove an edge, which starts at source and points to dest
 */
void graph_matrix_remove_edge(graph_matrix *graph, const char *source, const char *dest) {
  if (graph == NULL || source == NULL || dest == NULL) {
    log_error(null_pointer);
    return;
  }
  size_t source_pos = get_position_of_node(graph, source);
  size_t dest_pos = get_position_of_node(graph, dest);
  if (source_pos == graph->size || dest_pos == graph->size) {
    log_error(node_doesnt_exist);
    return;
  }
  graph->edges[dest_pos * graph->size + source_pos] = false;
}

/**
 * frees the graph and its elements
 */
void graph_matrix_destroy(graph_matrix *graph) {
  if (graph == NULL) {
    log_error(null_pointer);
  }
  free(graph->edges);
  for (size_t i = 0; i < graph->size; i++) {
    if (graph->nodes[i].value != NULL) {
      free(graph->nodes[i].value);
    }
  }
  free(graph->nodes);
  graph->nodes = NULL;
  graph->edges = NULL;
}

/** TOPOLOGICAL SORT **/
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

/**
 * @returns the next index were the value is NULL
 * or the size of the graph if there is no empty index.
 */
static size_t get_next_empty_index(const graph_matrix *graph) {
  for (size_t i = 0; i < graph->size; i++) {
    if (graph->nodes[i].value == NULL) {
      return i;
    }
  }
  return graph->size;
}

/**
 * Calculates the size which needs to be allocated for the nodes array.
 * @returns the new size which should be allocated
 */
static void set_next_size(graph_matrix *graph) {
  graph->size = graph->size * MULT_FACTOR;
}

static void expand_graph(graph_matrix *graph) {
  size_t old_size = graph->size;
  set_next_size(graph);
  // realloc either expands the allocated block or moves it to another address
  graph->nodes = realloc(graph->nodes, graph->size * sizeof(node));
  bool *new_edges = calloc(graph->size * graph->size, sizeof(bool));
  exit_on_mem_error(graph->nodes == NULL || graph->edges == NULL);

  // Initialize new block of memory
  for (size_t i = 0; i < old_size; i++) {
    for (size_t j = 0; j < old_size; j++) {
      new_edges[i * graph->size + j] = graph->edges[i * old_size + j];
    }
  }
  for(size_t i = old_size; i < graph->size; i++) {
    graph->nodes[i].value = NULL;
  }
  free(graph->edges);
  graph->edges = new_edges;
}

/**
 * @returns either the index of the node or the size of the graph if the node cannot be found
 */
static size_t get_position_of_node(graph_matrix *graph, const char *value) {
  for (size_t i = 0; i < graph->size; i++) {
    if (graph->nodes[i].value != NULL && strcmp(value, graph->nodes[i].value) == 0) {
      return i;
    }
  }
  return graph->size;
}
