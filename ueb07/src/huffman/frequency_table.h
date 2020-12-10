//
// Created by florian on 09.12.20.
//

#pragma once

#include <map>
#include <set>
#include "bit_stream.h"
#include "char_frequency.h"

namespace huffman {
  class frequency_table {
    private:
      std::map<char, int> frequencies;
      size_t total = 0;

    public:
      explicit frequency_table(const std::string &str);

      void print_frequencies() const;

      //huffman::char_frequency find_pair_at(char key) const;

      std::set<char_frequency> to_set() const;
  };
}
