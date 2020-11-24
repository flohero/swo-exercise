#ifndef SWO3_GRAPH_LIST_H
#define SWO3_GRAPH_LIST_H

struct node_t;

typedef struct edge_t {
  struct edge_t *next; // The next edge
  struct node_t *dest; // The destination of this edge
} edge_t;

typedef struct node_t {
  char *value;
  edge_t *edges; // The starting node_t of the outgoing edges of this node_t
  struct node_t *next;
} node_t;

typedef struct graph_list {
  node_t *nodes;
} graph_list;


void graph_list_init(graph_list *graph);

void graph_list_add_node(graph_list *graph, const char *val);

void graph_list_add_edge(graph_list *graph, const char *source, const char *dest);

void graph_list_print(graph_list *graph);

void graph_list_remove_node(graph_list *graph, const char *value);

void graph_list_remove_edge(graph_list *graph, const char *source, const char *dest);

void graph_list_destroy(graph_list *graph);

#endif //SWO3_GRAPH_LIST_H
