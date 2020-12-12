//
// Created by florian on 12.12.20.
//

#include "bit_code.h"

#include <utility>
#include <iostream>

namespace huffman {
  huffman::bit_code::bit_code(std::vector<bool> bits):
  bits{std::move(bits)}{}

  void bit_code::print() const {
    for (auto it: this->bits) {
      std::cout << (it ? "1" : "0");
    }
  }
}
