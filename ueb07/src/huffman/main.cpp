#include "bit_string_stream.h"
#include "frequency_table.h"
#include "huffman_tree_node.h"

using namespace huffman;

int main() {
    bit_string_stream str_stream{"../resources/test.txt"};
    frequency_table freq{str_stream.load_file_content()};
    freq.print_frequencies();
    return EXIT_SUCCESS;
}
