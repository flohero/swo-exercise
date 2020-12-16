//
// Created by florian on 12.12.20.
//

#include "bit_code.h"

#include <utility>
#include <iostream>

namespace huffman {
  bit_code::bit_code(char key, std::vector<bool> bits) :
          key{key},
          bits{std::move(bits)}{}

  void bit_code::print() const {
    std::cout << this->to_string();
  }

  std::string bit_code::to_string() const {
    std::string code;
    for (auto it: this->bits) {
      code += (it ? "1" : "0");
    }
    return code;
  }

  char bit_code::get_character() const {
    return this->key;
  }
}
