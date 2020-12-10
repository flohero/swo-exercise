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
    int total;

    public:
    explicit char_frequency(char character, int frequency, int total);

  };
}

