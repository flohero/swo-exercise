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

      explicit bit_code(char key, std::vector<bool> bits);

      void print() const;

      [[nodiscard]] std::string to_string() const;

      [[nodiscard]] char get_character() const;

      bool operator<(bit_code other) const;

    private:
      char key = '\0';
      std::vector<bool> bits;
  };
}
