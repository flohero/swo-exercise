//
// Created by florian on 10.12.20.
//

#pragma once

#include "char_frequency.h"

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

      [[nodiscard]] huffman_tree_node * get_left() const;

      [[nodiscard]] huffman_tree_node * get_right() const;
      char_frequency get_value()const ;

      bool is_empty() const;

      huffman_tree_node &operator=(const huffman_tree_node &other);

      huffman_tree_node *operator+(huffman_tree_node *node);

      bool operator<(const huffman_tree_node &node) const;

  };
}

