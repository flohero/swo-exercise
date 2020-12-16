//
// Created by florian on 15.12.20.
//

#pragma once

#include "../huffman_tree/huffman_tree.h"
#include "bit_code.h"

namespace huffman {
  class bit_code_table {
    public:
      explicit bit_code_table(const huffman_tree &tree);

      [[nodiscard]] bit_code find_code_of_char(char key) const;

      void print(const std::vector<char> &ordering) const;

      [[nodiscard]] std::vector<bit_code> all_codes() const;

    private:
      std::vector<bit_code> bit_codes;

      void
      bit_code_table_rec(const huffman_tree_node *node,
                         const std::vector<bool> &bit_vec = std::vector<bool>{});

  };
}

