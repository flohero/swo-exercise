//
// Created by florian on 10.12.20.
//

#pragma once

#include "../frequencies/char_frequency.h"

namespace huffman {
  class huffman_tree_node {
    private:
      huffman_tree_node *left;
      huffman_tree_node *right;
      char_frequency value;

    public:
      huffman_tree_node();

      explicit huffman_tree_node(char_frequency char_frequency);

      explicit huffman_tree_node(char_frequency char_frequency, huffman_tree_node *node1, huffman_tree_node *node2);

      ~huffman_tree_node();

      /**
       * Comparator function for two huffman_tree_nodes
       */
      struct comparator {
        bool operator()(huffman_tree_node *l, const huffman_tree_node *r) const {
          return *l < *r;
        }
      };

      [[nodiscard]] huffman_tree_node *get_left() const;

      [[nodiscard]] huffman_tree_node *get_right() const;

      [[nodiscard]] char_frequency get_value() const;

      [[nodiscard]] bool is_leaf() const;

      huffman_tree_node *operator+(huffman_tree_node *node);

      bool operator<(const huffman_tree_node &node) const;

  };
}

