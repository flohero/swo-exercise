//
// Created by florian on 14.12.20.
//

#include "huffman_tree.h"

namespace huffman {
  huffman_tree::huffman_tree(const frequency_table &freq_table) {
    auto freq_set = freq_table.to_set();
    while (freq_set.size() > 1) {
      huffman_tree_node *first = *freq_set.begin();
      huffman_tree_node *second = *std::next(freq_set.begin(), 1);
      huffman_tree_node *node = *first + second;
      freq_set.erase(first);
      freq_set.erase(second);
      freq_set.insert(node);
    }
    this->root = *freq_set.begin();
  }

  huffman_tree::~huffman_tree() {
    delete this->root;
  }

  /**
   * @returns the root of the tree
   */
  huffman_tree_node *huffman_tree::get_root() const  {
    return this->root;
  }
}