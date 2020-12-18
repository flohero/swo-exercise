//
// Created by florian on 15.12.20.
//

#include <iostream>
#include "bit_code_table.h"
#include "../utils.h"

namespace huffman {

  bit_code_table::bit_code_table(const huffman_tree &tree) {
    auto root = tree.get_root();
    // If the tree is from the beginning empty, just use a null vector.
    if (root->is_leaf()) {
      std::vector<bool> null_vec{};
      null_vec.push_back(false);
      this->bit_codes.emplace_back(root->get_value().get_character(), null_vec);
    } else {
      this->bit_code_table_rec(root);
    }
  }

  /**
   * find the bit_code of a char
   * @param key the char to find the bit_code for
   * @returns the bti_code of the char
   * @throws runtime_error if the bit_code could not be found
   */
  bit_code bit_code_table::find_code_of_char(const char key) const {
    for(auto it: this->bit_codes) {
      if(it.get_character() == key) {
        return it;
      }
    }
    throw std::runtime_error("Bit Code could not be found");
  }

  std::vector<bit_code> bit_code_table::all_codes() const {
    return this->bit_codes;
  }

  /**
   * A simple print which is ordered by the keys
   * @param ordering in which order the table should be printed
   */
  void bit_code_table::print(const std::vector<char>& ordering) const {
    std::cout << std::endl;
    std::cout << "Coding Table" << std::endl
              << "------------" << std::endl;
    for (const auto &it: ordering) {
      auto code = this->find_code_of_char(it);
      std::cout << utils::escape_char_to_printable(code.get_character());
      std::cout << "| ";
      code.print();
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }

  /**
   * Recursive function to build the bit_code_table.
   * Recursion floor is reached if the node is a leaf.
   * @param node
   * @param bit_vec the bit_code to reach the node from the root node
   */
  void bit_code_table::bit_code_table_rec(const huffman_tree_node *node,
                                          const std::vector<bool> &bit_vec) {
    if (node->is_leaf()) {
      bit_code code{node->get_value().get_character(), bit_vec};
      this->bit_codes.push_back(code);
      return;
    }
    std::vector<bool> left_bit_code{bit_vec};
    std::vector<bool> right_bit_code{bit_vec};
    left_bit_code.push_back(false);
    right_bit_code.push_back(true);
    this->bit_code_table_rec(node->get_left(), left_bit_code);
    this->bit_code_table_rec(node->get_right(), right_bit_code);
  }
}
