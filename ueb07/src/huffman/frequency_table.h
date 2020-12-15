//
// Created by florian on 09.12.20.
//

#pragma once

#include <map>
#include <set>
#include <vector>
#include "char_frequency.h"
#include "huffman_tree/huffman_tree_node.h"

namespace huffman {
  class frequency_table {
    private:
      std::map<char, int> frequencies;
      size_t total = 0;


    public:
      explicit frequency_table(const std::string &str);

      void print() const;

      [[nodiscard]] std::vector<char> keys() const;

      static void delete_huffman_frequency_set(
              const std::set<huffman_tree_node *, huffman_tree_node::comparator> &set);

      [[nodiscard]] std::set<huffman_tree_node *, huffman_tree_node::comparator> to_set() const;
  };
}
