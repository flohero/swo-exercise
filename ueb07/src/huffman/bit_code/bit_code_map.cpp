//
// Created by florian on 15.12.20.
//

#include "bit_code_map.h"

namespace huffman {

  bit_code_map::bit_code_map(const huffman_tree &tree) {
    auto root = tree.get_root();
    // If the tree is from the beginning empty, just use a null vector.
    if (root->is_leaf()) {
      std::vector<bool> null_vec{};
      null_vec.push_back(false);
      this->bit_code_mapping.insert({root->get_value().get_character(), bit_code{null_vec}});
    } else {
      this->coding_map_rec(this->bit_code_mapping, root);
    }
  }

  void bit_code_map::coding_map_rec(std::map<const char, bit_code> &codes,
                                    const huffman_tree_node *node,
                                    const std::vector<bool> &bit_vec) const {
    if (node->is_leaf()) {
      codes.insert({node->get_value().get_character(), bit_code{bit_vec}});
      return;
    }
    std::vector<bool> left_bit_code{bit_vec};
    std::vector<bool> right_bit_code{bit_vec};
    left_bit_code.push_back(false);
    right_bit_code.push_back(true);
    this->coding_map_rec(codes, node->get_left(), left_bit_code);
    this->coding_map_rec(codes, node->get_right(), right_bit_code);
  }

  std::map<const char, bit_code> &bit_code_map::codes() {
    return this->bit_code_mapping;
  }

}
