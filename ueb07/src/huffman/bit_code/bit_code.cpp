//
// Created by florian on 12.12.20.
//

#include "bit_code.h"

#include <utility>
#include <iostream>

namespace huffman {
  huffman::bit_code::bit_code(std::vector<bool> bits) :
          bits{std::move(bits)} {}

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
}
