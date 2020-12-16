#include "content/huffman_default_content.h"

using namespace huffman;

int main() {
  huffman_default_content c{"AACCCNNDDDAACCCCCRRAACCCCNNNADDDDDCCCAAACCNAAAAACCDDDDRRAAAANCCCRRAAAAARRRCCCCAARRAAAAAAACCCRRRRNCCC"};
  c.statistics();
  return EXIT_SUCCESS;
}
