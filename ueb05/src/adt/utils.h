#ifndef SWO3_UTILS_H
#define SWO3_UTILS_H

typedef enum error_type {
  out_of_memory,
  node_doesnt_exist,
  node_already_exists,
  edge_already_exists,
  null_pointer,
  cyclic_graph
} error_type;

void log_error(error_type error, const char *func_name, int line);

void exit_on_mem_error(bool expr, const char *func_name, int line);

#endif //SWO3_UTILS_H
