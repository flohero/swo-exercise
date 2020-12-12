#include "bit_stream/bit_string_stream.h"
#include "bit_stream/default_stream.h"
#include "coding_token.h"
#include "content/huffman_content.h"
#include "content/huffman_default_content.h"

using namespace huffman;

int main() {
  huffman_default_content c{"AACCCNNDDDAACCCCCRRAACCCCNNNADDDDDCCCAAACCNAAAAACCDDDDRRAAAANCCCRRAAAAARRRCCCCAARRAAAAAAACCCRRRRNCCC"};
  c.encode();
  return EXIT_SUCCESS;
}
