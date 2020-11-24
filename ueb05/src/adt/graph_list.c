#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include <stdbool.h>
#include "graph_list.h"
#include "utils.h"

#define log_error(type) log_error((type), __func__, __LINE__);

#define exit_on_mem_error(expr) exit_on_mem_error((expr), __func__, __LINE__)

static void destroy_node(node_t *node);

static node_t *find_node_in_list(graph_list *graph, const char *value);

static void graph_list_delete_all_edges_of_node(graph_list *graph, node_t *node);

void graph_list_init(graph_list *graph) {
  graph->nodes = NULL;
}

void graph_list_add_node(graph_list *graph, const char *val) {
  node_t *new_node = malloc(sizeof(node_t));
  exit_on_mem_error(new_node == NULL);
  if (graph->nodes != NULL) {
    node_t *last_node = NULL;
    for (node_t *n_ptr = graph->nodes; n_ptr != NULL; n_ptr = n_ptr->next) {
      if (strcmp(n_ptr->value, val) == 0) {
        log_error(node_already_exists);
        return;
      }
      last_node = n_ptr;
    };
    last_node->next = new_node;
  } else {
    graph->nodes = new_node;
  }
  char *cpy = malloc((strlen(val) + 1) * sizeof(char));
  exit_on_mem_error(cpy == NULL || new_node == NULL);
  strcpy(cpy, val);
  new_node->value = cpy;
  new_node->next = NULL;
  new_node->edges = NULL;
}

void graph_list_add_edge(graph_list *graph, const char *source, const char *dest) {
  if (graph == NULL || source == NULL || dest == NULL) {
    log_error(null_pointer);
    return;
  }
  node_t *source_node = find_node_in_list(graph, source);
  node_t *dest_node = find_node_in_list(graph, dest);
  if (source_node == NULL || dest_node == NULL) {
    log_error(node_doesnt_exist);
    return;
  }
  edge_t *new_edge = malloc(sizeof(edge_t));
  exit_on_mem_error(new_edge == NULL);
  if (source_node->edges == NULL) {
    source_node->edges = new_edge;
  } else {
    edge_t *last_edge = source_node->edges;
    for (edge_t *edge = source_node->edges; edge != NULL; edge = edge->next) {
      if (edge->dest == dest_node) {
        log_error(edge_already_exists);
        return;
      }
      last_edge = edge;
    }
    last_edge->next = new_edge;
  }
  new_edge->next = NULL;
  new_edge->dest = dest_node;
}

void graph_list_print(graph_list *graph) {
  for (node_t *node = graph->nodes; node != NULL; node = node->next) {
    printf("%s: ", node->value);
    for (edge_t *edge = node->edges; edge != NULL; edge = edge->next) {
      printf("\"%s\" ", edge->dest->value);
    }
    printf("\n");
  }
}

void graph_list_remove_node(graph_list *graph, const char *value) {
  if (value == NULL) {
    log_error(null_pointer);
    return;
  }
  node_t *node = find_node_in_list(graph, value);
  if (node == NULL) {
    log_error(node_doesnt_exist);
    return;
  }
  if (node == graph->nodes) {
    node_t *next_node = node->next;
    graph_list_delete_all_edges_of_node(graph, node);
    destroy_node(node);
    graph->nodes = next_node;
  } else {
    node_t *next_node = node->next;
    node_t *prev_node = NULL;
    // Get the previous node
    bool found = false;
    for(node_t *n = graph->nodes; n != NULL && !found; n = n->next) {
      if(n == node) {
        found = true;
      } else {
        prev_node = n;
      }
    }
    graph_list_delete_all_edges_of_node(graph, node);
    destroy_node(node);
    prev_node->next = next_node;
  }
}

void graph_list_remove_edge(graph_list *graph, const char *source, const char *dest) {
  if(graph == NULL  || source == NULL || dest == NULL) {
    log_error(null_pointer);
    return;
  }
  node_t *source_node = find_node_in_list(graph, source);
  node_t *dest_node = find_node_in_list(graph, dest);
  if(source_node == NULL || dest_node == NULL) {
    log_error(node_doesnt_exist);
    return;
  }
  edge_t *prev_edge = NULL;
  for(edge_t *edge = source_node->edges; edge != NULL; edge = edge->next) {
    if(edge->dest == dest_node) {
      if(prev_edge == NULL) {
        source_node->edges = edge->next;
      } else {
        prev_edge->next = edge->next;
      }
      free(edge);
      return;
    }
    prev_edge = edge;
  }
}

void graph_list_destroy(graph_list *graph) {
  for(node_t *node = graph->nodes; node != NULL;) {
    for(edge_t *edge = node->edges; edge != NULL; ) {
      edge_t *prev_edge = edge;
      edge = edge->next;
      free(prev_edge);
    }
    node_t *prev_node = node;
    node = node->next;
    destroy_node(prev_node);
  }
}

static node_t *find_node_in_list(graph_list *graph, const char *value) {
  for (node_t *n = graph->nodes; n != NULL; n = n->next) {
    if (strcmp(n->value, value) == 0) {
      return n;
    }
  }
  return NULL;
}

static void destroy_node(node_t *node) {
    free(node->value);
    free(node);
}

static void graph_list_delete_all_edges_of_node(graph_list *graph, node_t *node) {
  // Delete all outcoming edges
  for (edge_t *edge = node->edges; edge != NULL;) {
    edge_t *old_edge = edge;
    edge = edge->next;
    free(old_edge);
  }
  node->edges = NULL;

  // Delete all incoming edges
  for (node_t *other_node = graph->nodes; other_node != NULL; other_node = other_node->next) {
    edge_t *prev_edge = NULL;
    bool deleted = false;
    edge_t *edge_to_delete = NULL;
    for (edge_t *edge = other_node->edges; edge != NULL && !deleted;) {
      if (edge->dest == node) {
        // if it is the first edge in the list, prev_edge will be NULL
        if (prev_edge == NULL) {
          other_node->edges = edge->next;
        } else {
          prev_edge->next = edge->next;
        }
        edge_to_delete = edge;
        deleted = true;
        continue;
      } else {
        prev_edge = edge;
        edge = edge->next;
      }
    }
    if(edge_to_delete != NULL) {
      free(edge_to_delete);
    }
  }
}


