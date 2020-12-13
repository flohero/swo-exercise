//
// Created by florian on 09.12.20.
//

#pragma once

#include <map>
#include <set>
#include <vector>
#include "bit_stream/bit_stream.h"
#include "char_frequency.h"
#include "huffman_tree_node.h"

namespace huffman {
  class frequency_table {
    private:
      std::map<char, int> frequencies;
      size_t total = 0;


    public:
      /**
       * Comparator function for two huffman_tree_nodes
       */
      struct comp {
        bool operator()(huffman_tree_node *l, const huffman_tree_node *r) const {
          return *l < *r;
        }
      };

      explicit frequency_table(const std::string &str);

      void print() const;

      [[nodiscard]] huffman_tree_node *build_tree() const;

      [[nodiscard]] std::vector<char> keys() const;

      [[nodiscard]] std::set<huffman_tree_node *, comp> to_set() const;


      static void delete_huffman_frequency_set(const std::set<huffman_tree_node *, frequency_table::comp> &set);
  };
}
