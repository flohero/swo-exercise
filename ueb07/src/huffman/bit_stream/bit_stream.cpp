//
// Created by florian on 08.12.20.
//

#include "bit_stream.h"

#include <utility>

using std::string;

namespace huffman {
  bit_stream::bit_stream(string filename) {
    this->filename = std::move(filename);
  }
}

