//
// Created by florian on 10.12.20.
//

#include "huffman_tree_node.h"

namespace huffman {
  huffman_tree_node::huffman_tree_node() {
    this->left = nullptr;
    this->right = nullptr;
  }

  huffman_tree_node::huffman_tree_node(char_frequency char_frequency) {
    this->value = char_frequency;
    this->left = nullptr;
    this->right = nullptr;
  }

  huffman_tree_node::huffman_tree_node(char_frequency char_frequency, huffman_tree_node *node1,
                                       huffman_tree_node *node2)
          : huffman_tree_node(char_frequency) {
    if (node1 < node2) {
      this->left = node1;
      this->right = node2;
    } else {
      this->left = node2;
      this->right = node1;
    }
  }

  huffman_tree_node::~huffman_tree_node() {
    delete this->left;
    delete this->right;
  }

  huffman_tree_node &huffman_tree_node::operator=(const huffman_tree_node &other) {
    if (this != &other) {
      delete this->left;
      delete this->right;
      this->value = other.value;
      this->left = other.left;
      this->right = other.right;
    }
    return *this;
  }

  /**
   * Overload the plus operator to add two trees together:
   * {freq={x, 1}, left=nullptr, right=nullptr} + {freq={y, 2}, left=nullptr, right=nullptr}
   *    = {freq={-, 3}, left={freq={x, 1}, left=nullptr, right=nullptr}, right={freq={y, 2}, left=nullptr, right=nullptr}
   * @param node the other node to add to, can't be const since it can be changed later
   * @return
   */
  huffman_tree_node *huffman_tree_node::operator+(huffman_tree_node *node) {
    return new huffman_tree_node(this->value.operator+(node->value), this, node);
  }

  bool huffman_tree_node::operator<(const huffman_tree_node &node) {
    return this->value < node.value;
  }
}