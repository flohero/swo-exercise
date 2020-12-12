#include "bit_stream/bit_string_stream.h"
#include "bit_stream/default_stream.h"
#include "frequency_table.h"
#include "huffman_tree_node.h"
#include "coding_token.h"

using namespace huffman;

int main() {
  //bit_string_stream str_stream{"../resources/example.txt"};
  //default_stream stream{"AACCCNNDDDAACCCCCRRAACCCCNNNADDDDDCCCAAACCNAAAAACCDDDDRRAAAANCCCRRAAAAARRRCCCCAARRAAAAAAACCCRRRRNCCC"};
  default_stream stream{""};
  /*frequency_table freq{str_stream.content()};
  freq.print_frequencies();
  auto tree = freq.build_tree();
  delete tree;*/
  coding_token ct{stream};
  auto m = ct.coding_map();
  delete m;
  return EXIT_SUCCESS;
}
