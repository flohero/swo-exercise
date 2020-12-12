//
// Created by florian on 09.12.20.
//

#pragma once


#include <utility>
#include <map>

namespace huffman {
  class char_frequency {
    private:
      char character;
      int frequency;
      size_t total;

    public:
      char_frequency();

      explicit char_frequency(char character, int frequency, size_t total);

      char_frequency operator+(const char_frequency &freq) const;

      bool operator<(const char_frequency &freq) const;

      bool operator>(const char_frequency &freq) const;

      char get_character() const;
  };
}

