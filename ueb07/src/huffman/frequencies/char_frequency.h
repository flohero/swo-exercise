//
// Created by florian on 09.12.20.
//

#pragma once


#include <utility>
#include <map>

namespace huffman {
  class char_frequency {
    private:
      static int count;
      int id = count++;
      char character;
      int frequency;
      size_t total;

    public:
      char_frequency();

      explicit char_frequency(char character, int frequency, size_t total);

      char_frequency operator+(const char_frequency &freq) const;

      bool operator<(const char_frequency &freq) const;

      bool operator>(const char_frequency &freq) const;

      [[nodiscard]] char get_character() const;

      [[nodiscard]] std::string to_string() const;
  };
}

