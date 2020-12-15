//
// Created by florian on 11.12.20.
//

#pragma once


#include <string>
#include <vector>
#include "bit_stream/bit_stream.h"
#include "frequency_table.h"
#include "bit_code/bit_code.h"
#include "huffman_tree/huffman_tree.h"
#include "bit_code/bit_code_map.h"

namespace huffman {
  class coding_token {
    private:
      frequency_table freq_table;
      huffman_tree tree;
      bit_code_map code_map;

    public:
      explicit coding_token(const std::string& content);

      [[nodiscard]] std::map<const char, bit_code> &coding_map();

      void print();


  };
}

