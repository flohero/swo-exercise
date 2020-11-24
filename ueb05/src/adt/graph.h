#ifndef SWO3_GRAPH_H
#define SWO3_GRAPH_H

#include "graph_matrix.h"
#include "graph_list.h"

#if defined USE_GRAPH_LIST
typedef graph_list graph_t;

#define graph_init graph_list_init
#define graph_add_node graph_list_add_node
#define graph_add_edge graph_list_add_edge
#define graph_print graph_list_print
#define graph_remove_node graph_list_remove_node
#define graph_remove_edge graph_list_remove_edge
#define graph_destroy graph_list_destroy

#elif defined USE_GRAPH_MATRIX
typedef graph_matrix graph_t;

#define graph_init graph_matrix_init
#define graph_add_node graph_matrix_add_node
#define graph_add_edge graph_matrix_add_edge
#define graph_print graph_matrix_print
#define graph_remove_node graph_matrix_remove_node
#define graph_remove_edge graph_matrix_remove_edge
#define graph_destroy graph_matrix_destroy
#define graph_topological_sort graph_matrix_topological_sort

#else
#error "Define onl< one of 'USE_GRAPH_LIST' or 'USE_GRAPH_MATRIX'."
#endif
#endif //SWO3_GRAPH_H
