//
// Created by florian on 12.12.20.
//

#pragma once

#include <vector>

namespace huffman {
  class bit_code {
    public:
      explicit bit_code(std::vector<bool> bits);

      void print() const;
    private:
      std::vector<bool> bits;
  };
}
