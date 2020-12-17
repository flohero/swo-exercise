//
// Created by florian on 08.12.20.
//

#include <fstream>
#include <iostream>
#include "bit_string_stream.h"

namespace huffman {

  bit_string_stream::bit_string_stream(const std::string &filename)
          : bit_stream(filename) {}

  /**
   * @returns the content of a file
   * @throws runtime_error if the file could not be opened,
   * this could happen if the file does not exist or is already open elsewhere
   */
  std::string bit_string_stream::content() const {
    std::ifstream ifs(this->filename, std::ifstream::in);
    if(!ifs.good()) {
      throw std::runtime_error("Could not open file: " + this->filename);
    }
    std::string str;
    for (char c = static_cast<char>(ifs.get()); ifs.good() && c != -1; c = static_cast<char>(ifs.get())) {
      str += c;
    }
    ifs.close();
    return str;
  }
}
