//
// Created by florian on 10.12.20.
//

#include <iostream>
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

  /**
   * Construct the node and sort the nodes into the left and right node.
   * @param char_frequency
   * @param node1
   * @param node2
   */
  huffman_tree_node::huffman_tree_node(char_frequency char_frequency, huffman_tree_node *node1,
                                       huffman_tree_node *node2)
          : huffman_tree_node(char_frequency) {
    if (*node1 < *node2) {
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

  /**
   * Overload the plus operator to add two trees together.
   * The two containing char_frequencies will also be added and put into the resulting root-node.
   * {freq={x, 1}, left=nullptr, right=nullptr} + {freq={y, 2}, left=nullptr, right=nullptr}
   *    = {freq={-, 3}, left={freq={x, 1}, left=nullptr, right=nullptr}, right={freq={y, 2}, left=nullptr, right=nullptr}
   * @param node the other node to add to, can't be const since it can be changed later
   * @return
   */
  huffman_tree_node *huffman_tree_node::operator+(huffman_tree_node *node) {
    return new huffman_tree_node(this->value.operator+(node->value), this, node);
  }

  /**
   * The node is smaller if the char_frequency is smaller
   * @param node
   * @returns if the huffman_tree_node is smaller than the other
   */
  bool huffman_tree_node::operator<(const huffman_tree_node &node) const {
    return this->value < node.value;
  }

  huffman_tree_node *huffman_tree_node::get_left() const {
    return this->left;
  }

  huffman_tree_node *huffman_tree_node::get_right() const {
    return this->right;
  }

  /**
   * @returns if this huffman_tree_node is a leaf
   */
  bool huffman_tree_node::is_leaf() const {
    return this->left == nullptr && this->right == nullptr;
  }

  char_frequency huffman_tree_node::get_value() const {
    return this->value;
  }

  /**
   * Print this node and following nodes
   */
  void huffman_tree_node::print() {
    std::cout << "Huffman Tree" << std::endl;
    print_rec("", false);
  }

  /**
   * Recursively iterates over a tree and prints its nodes.
   * Recursion floor is reached when node is a leaf.
   * @param prefix a string prefix
   * @param is_right distinguish between left and right nodes
   */
  void huffman_tree_node::print_rec(const std::string &prefix, bool is_right) {

    std::cout << prefix;

    std::cout << (is_right ? "├──" : "└──");

    std::cout << this->value.to_string() << std::endl;

    if(this->is_leaf()) {
      return;
    }
    this->right->print_rec(prefix + (is_right ? "│   " : "    "), true);
    this->left->print_rec(prefix + (is_right ? "│   " : "    "), false);
  }
}
