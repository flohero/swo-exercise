//
// Created by florian on 11.12.20.
//

#pragma once


#include <string>
#include <vector>
#include "bit_stream/bit_stream.h"
#include "frequencies/frequency_table.h"
#include "bit_code/bit_code.h"
#include "huffman_tree/huffman_tree.h"
#include "bit_code/bit_code_table.h"

namespace huffman {
  class coding_token {
    private:
      frequency_table freq_table;
      huffman_tree tree;
      bit_code_table code_table;

    public:
      explicit coding_token(const std::string& content);

      void print();

      [[nodiscard]] bit_code char_to_bitcode(char key) const;

      [[nodiscard]] std::vector<bit_code> codes() const;
  };
}

