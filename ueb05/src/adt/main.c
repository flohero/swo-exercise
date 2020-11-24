#include <stdlib.h>
#include <stdio.h>
//#define USE_GRAPH_LIST
#include "graph.h"

void reset_graph(graph_t *graph) {
  graph_destroy(graph);
  graph_init(graph);
  graph_add_node(graph, "A");
  graph_add_node(graph, "B");
  graph_add_node(graph, "C");
  graph_add_node(graph, "D");
  graph_add_node(graph, "E");
  graph_add_edge(graph, "A", "B");
  graph_add_edge(graph, "A", "D");
  graph_add_edge(graph, "A", "C");
  graph_add_edge(graph, "A", "E");
  graph_add_edge(graph, "B", "D");
  graph_add_edge(graph, "C", "B");
  graph_add_edge(graph, "C", "E");
}

int main(void) {
  graph_t graph;
  graph_init(&graph);
  // Insert already existing Node
  graph_add_node(&graph, "A");
  graph_add_node(&graph, "A");
  // Insert Nodes
  graph_add_node(&graph, "B");
  graph_add_node(&graph, "C");
  graph_add_node(&graph, "D");
  graph_add_node(&graph, "E");

  // Insert already existing Edge
  graph_add_edge(&graph, "A", "B");
  graph_add_edge(&graph, "A", "B");
  // Insert Edge with not existing Node
  graph_add_edge(&graph, "F", "B");
  graph_add_edge(&graph, "A", "F");

  // Insert Edges
  graph_add_edge(&graph, "A", "D");
  graph_add_edge(&graph, "A", "C");
  graph_add_edge(&graph, "A", "E");

  graph_add_edge(&graph, "B", "D");

  graph_add_edge(&graph, "C", "B");
  graph_add_edge(&graph, "C", "E");
  printf("\nResulting Graph:\n");
  graph_print(&graph);

  // Add self edge
  graph_add_edge(&graph, "A", "A");
  printf("\nGraph with A->A:\n");
  graph_print(&graph);

  // Remove Edge
  graph_remove_edge(&graph, "B", "D");

  printf("\nGraph with B->D removed:\n");
  graph_print(&graph);

  // Remove not existing edge
  graph_remove_edge(&graph, "B", "D");

  printf("\nGraph with B->D removed twice:\n");
  graph_print(&graph);

  // Remove Self-Edge
  graph_remove_edge(&graph, "A", "A");

  printf("\nGraph with A->A removed:\n");
  graph_print(&graph);

  // Remove node
  graph_remove_node(&graph, "A");
  printf("\nGraph with A removed:\n");
  graph_print(&graph);

  // Remove not existing Node
  graph_remove_node(&graph, "A");
  printf("\nGraph with A removed twice:\n");
  graph_print(&graph);

#ifdef USE_GRAPH_MATRIX
  //Non cyclical Graph
  reset_graph(&graph);
  printf("\nSorted:\n");
  graph_matrix_topological_sort(&graph);

  // Self Edge
  reset_graph(&graph);
  graph_add_edge(&graph, "A", "A");

  printf("\nSelf-Edge Graph:\n");
  graph_matrix_topological_sort(&graph);

  // Cycle
  reset_graph(&graph);
  graph_add_edge(&graph, "E", "A");
  graph_print(&graph);
  printf("\nCyclical Graph:\n");
  graph_matrix_topological_sort(&graph);
#endif
  graph_destroy(&graph);
  return EXIT_SUCCESS;
}

/*
graph_init(&graph);
printf("\nGraph:\n");
graph_print(&graph);
graph_add_node(&graph, "Hello");
graph_add_node(&graph, "Bye");
graph_add_node(&graph, "Hola");
graph_add_edge(&graph, "Hello", "Bye");
graph_add_edge(&graph, "Hello", "Hola");
graph_add_edge(&graph, "Bye", "Hello");
printf("\nGraph:\n");
graph_print(&graph);


printf("\nGraph:\n");
graph_print(&graph);

graph_remove_edge(&graph, "Bye", "Hello");
printf("\nGraph:\n");
graph_print(&graph);

graph_remove_node(&graph, "Bye");
printf("\nGraph: \n");
graph_print(&graph);
graph_destroy(&graph);*/
