//
// Created by florian on 11.12.20.
//

#include "coding_token.h"
#include "bit_code/bit_code.h"

namespace huffman {

  /**
   * Initialize the frequency_table, huffman_tree and bit_code_table.
   * These operations depend on each other.
   * @param content
   */
  coding_token::coding_token(const std::string& content) :
          freq_table{content},
          tree{freq_table},
          code_table{tree}{}

  /**
   * @returns a vector of bit_codes
   */
  std::vector<bit_code> coding_token::codes() const {
    return this->code_table.all_codes();
  }

  /**
   * Call the print function of frequency_table, huffman_tree und bit_code_table
   */
  void coding_token::print() {
    this->freq_table.print();
    this->code_table.print(this->freq_table.sorted_keys());
    this->tree.print();
  }

  /**
   * Find the bit_code of a char
   * @param key char to find
   * @returns the bit_code
   */
  bit_code coding_token::char_to_bitcode(const char key) const {
    return this->code_table.find_code_of_char(key);
  }
}
