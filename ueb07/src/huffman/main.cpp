#include "bit_stream/bit_string_stream.h"
#include "coding_token.h"
#include "content/huffman_default_content.h"

using namespace huffman;

int main() {
  huffman_default_content c{"AACCCNNDDDAACCCCCRRAACCCCNNNADDDDDCCCAAACCNAAAAACCDDDDRRAAAANCCCRRAAAAARRRCCCCAARRAAAAAAACCCRRRRNCCC"};
  c.statistics();
  return EXIT_SUCCESS;
}
