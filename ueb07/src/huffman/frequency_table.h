//
// Created by florian on 09.12.20.
//

#pragma once

#include <map>
#include <set>
#include <vector>
#include "bit_stream.h"
#include "char_frequency.h"
#include "huffman_tree_node.h"

namespace huffman {
  class frequency_table {
    private:
      struct comp;

      std::map<char, int> frequencies;
      size_t total = 0;


      [[nodiscard]] std::set<huffman_tree_node *, comp> to_set() const;

    public:
      explicit frequency_table(const std::string &str);

      void print_frequencies() const;

      //huffman::char_frequency find_pair_at(char key) const;

      [[nodiscard]] huffman_tree_node *build_tree() const;

      std::vector<char> keys() const;
  };
}
