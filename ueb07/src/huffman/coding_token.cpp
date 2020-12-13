//
// Created by florian on 11.12.20.
//

#include <iostream>
#include "coding_token.h"
#include "bit_code.h"

namespace huffman {

  coding_token::coding_token(bit_stream &bit_stream)
          : stream{bit_stream},
            freq_table{stream.content()} {

  }

  huffman_tree_node *coding_token::build_tree() const {
    return this->freq_table.build_tree();
  }

  std::map<const char,bit_code> *coding_token::coding_map() const {
    auto tree = this->build_tree();
    auto coding_map = new std::map<const char, bit_code>;
    for (auto key: this->freq_table.keys()) {
      coding_map->insert({key, bit_code{}});
    }
    // If the tree is from the beginning empty, just return a null vector.
    if(tree->is_empty()) {
      std::vector<bool> null_vec{};
      null_vec.push_back(false);
      coding_map->begin()->second = bit_code{null_vec};
    } else {
      this->coding_map_rec(*coding_map, tree);
    }
    delete tree;
    return coding_map;
  }

  void coding_token::coding_map_rec(std::map<const char, bit_code> &codes,
                                    const huffman_tree_node *node,
                                    const std::vector<bool>& bit_vec) const {
    char_frequency freq = node->get_value();
    if(node->is_empty()) {
      auto item = codes.find(freq.get_character());
      item->second = bit_code{bit_vec};
      return;
    }
    std::vector<bool> left_bit_code{bit_vec};
    std::vector<bool> right_bit_code{bit_vec};
    left_bit_code.push_back(false);
    right_bit_code.push_back(true);
    this->coding_map_rec(codes, node->get_left(), left_bit_code);
    this->coding_map_rec(codes, node->get_right(), right_bit_code);
  }

  void coding_token::print() const {
    this->freq_table.print();
    std::cout << std::endl;
    auto coding_map = this->coding_map();

    std::cout << "Coding Table" << std::endl
    << "------------" << std::endl;
    for(const auto& it: this->freq_table.to_set()) {
      auto codes = coding_map->find(it->get_value().get_character());
      std::cout << codes->first << " | ";
      codes->second.print();
      std::cout << std::endl;
    }
    delete coding_map;
  }
}