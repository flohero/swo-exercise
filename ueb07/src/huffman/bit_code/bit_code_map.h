//
// Created by florian on 15.12.20.
//

#pragma once

#include "../huffman_tree/huffman_tree.h"
#include "bit_code.h"

namespace huffman {
  class bit_code_map {
    public:
      explicit bit_code_map(const huffman_tree &tree);

      std::map<const char, bit_code> &codes();

    private:
      std::map<const char, bit_code> bit_code_mapping;

      void
      coding_map_rec(std::map<const char, bit_code> &codes, const huffman_tree_node *node,
                     const std::vector<bool> &bit_vec = std::vector<bool>{}) const;
  };
}

