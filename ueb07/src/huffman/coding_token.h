//
// Created by florian on 11.12.20.
//

#pragma once


#include <string>
#include <vector>
#include "bit_stream.h"
#include "frequency_table.h"

namespace huffman {
  class coding_token {
    private:
      bit_stream &stream;
      frequency_table freq_table;

      [[nodiscard]] huffman_tree_node *build_tree() const;

      void coding_map_rec(std::map<const char, std::vector<bool>> &codes,
                          const huffman_tree_node *node,
                          const std::vector<bool>& = std::vector<bool>{}) const;

    public:
      explicit coding_token(bit_stream &bit_stream);

      [[nodiscard]] std::map<const char, std::vector<bool>> *coding_map() const;
  };
}

