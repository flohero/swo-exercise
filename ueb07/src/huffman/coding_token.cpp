//
// Created by florian on 11.12.20.
//

#include "coding_token.h"
#include "bit_code/bit_code.h"

namespace huffman {

  coding_token::coding_token(const std::string& content) :
          freq_table{content},
          tree{freq_table},
          code_table{tree}{}

  std::vector<bit_code> coding_token::codes() const {
    return this->code_table.all_codes();
  }

  void coding_token::print() {
    this->freq_table.print();
    this->code_table.print(this->freq_table.sorted_keys());
  }

  bit_code coding_token::char_to_bitcode(const char key) const {
    return this->code_table.find_code_of_char(key);
  }
}
