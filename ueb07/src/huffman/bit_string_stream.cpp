//
// Created by florian on 08.12.20.
//

#include <fstream>
#include <iostream>
#include "bit_string_stream.h"

namespace huffman {

  bit_string_stream::bit_string_stream(const std::string &filename) : bit_stream(filename) {
  }

  std::string bit_string_stream::load_file_content() const {
    std::ifstream ifs(this->filename, std::ifstream::in);
    std::string str;
    for (char c = static_cast<char>(ifs.get()); ifs.good() && c != -1; c = static_cast<char>(ifs.get())) {
      str += c;
    }
    ifs.close();
    return str;
  }
}
