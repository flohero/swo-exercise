//
// Created by florian on 12.12.20.
//

#pragma once

#include <vector>
#include <string>

namespace huffman {
  class bit_code {
    public:
      bit_code() = default;

      explicit bit_code(std::vector<bool> bits);

      void print() const;

      [[nodiscard]] std::string to_string() const;

    private:
      std::vector<bool> bits;

  };
}
