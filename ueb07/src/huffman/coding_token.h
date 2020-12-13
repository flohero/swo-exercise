//
// Created by florian on 11.12.20.
//

#pragma once


#include <string>
#include <vector>
#include "bit_stream/bit_stream.h"
#include "frequency_table.h"
#include "bit_code.h"

namespace huffman {
  class coding_token {
    private:
      frequency_table freq_table;

      [[nodiscard]] huffman_tree_node *build_tree() const;

      void coding_map_rec(std::map<const char, bit_code> &codes,
                          const huffman_tree_node *node,
                          const std::vector<bool> &bit_vec = std::vector<bool>{}) const;

    public:
      explicit coding_token(const std::string& content);

      [[nodiscard]] std::map<const char, bit_code> *coding_map() const;

      void print() const;


  };
}

