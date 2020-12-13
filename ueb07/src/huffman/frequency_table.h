//
// Created by florian on 09.12.20.
//

#pragma once

#include <map>
#include <set>
#include <vector>
#include "char_frequency.h"
#include "huffman_tree_node.h"

namespace huffman {
  class frequency_table {
    private:
      /**
       * Comparator function for two huffman_tree_nodes
       */
      struct huffman_tree_node_comperator {
        bool operator()(huffman_tree_node *l, const huffman_tree_node *r) const {
          return *l < *r;
        }
      };

      std::map<char, int> frequencies;
      size_t total = 0;

      [[nodiscard]] std::set<huffman_tree_node *, huffman_tree_node_comperator> to_set() const;


    public:
      explicit frequency_table(const std::string &str);

      void print() const;

      [[nodiscard]] huffman_tree_node *build_tree() const;

      [[nodiscard]] std::vector<char> keys() const;

      static void delete_huffman_frequency_set(
              const std::set<huffman_tree_node *, frequency_table::huffman_tree_node_comperator> &set);
  };
}
