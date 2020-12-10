//
// Created by florian on 09.12.20.
//

#include "char_frequency.h"
namespace huffman {

  char_frequency::char_frequency(const char character, const int frequency, const int total) {
    this->total = total;
    this->character = character;
    this->frequency = frequency;
  }
}