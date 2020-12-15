//
// Created by florian on 11.12.20.
//

#include <iostream>
#include "coding_token.h"
#include "bit_code/bit_code.h"

namespace huffman {

  coding_token::coding_token(const std::string& content) :
          freq_table{content},
          tree{freq_table},
          code_map{tree}{}


  std::map<const char, bit_code> &coding_token::coding_map() {
    return this->code_map.codes();
  }

  void coding_token::print() {
    this->freq_table.print();
    std::cout << std::endl;
    auto coding_map = this->coding_map();

    std::cout << "Coding Table" << std::endl
              << "------------" << std::endl;
    auto keys = this->freq_table.keys();
    for (const auto &it: keys) {
      auto codes = coding_map.find(it);
      std::cout << codes->first << " | ";
      codes->second.print();
      std::cout << std::endl;
    }
  }
}
