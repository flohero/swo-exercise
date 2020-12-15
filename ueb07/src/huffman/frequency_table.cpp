//
// Created by florian on 09.12.20.
//

#include <iostream>
#include "frequency_table.h"

using std::cout;
using std::endl;

namespace huffman {
  frequency_table::frequency_table(const std::string &str) {
    total = str.length();
    if (total == 0) {
      throw std::invalid_argument{"Content was empty"};
    }
    for (char c: str) {
      auto res = this->frequencies.insert({c, 1});
      if (!res.second
          && res.first != this->frequencies.end()) {
        res.first->second++;
      }
    }
  }

  /**
   * Convert the Frequency Table to a set
   * @returns a sorted set
   */
  std::set<huffman_tree_node *, huffman_tree_node::comparator> frequency_table::to_set() const {
    std::set<huffman_tree_node *, huffman_tree_node::comparator> freq_set;
    for (auto frequency : this->frequencies) {
      auto *node = new huffman_tree_node{char_frequency{frequency.first, frequency.second, this->total}};
      freq_set.insert(node);
    }
    return freq_set;
  }

  std::vector<char> frequency_table::keys() const {
    std::vector<char> k;
    for (auto freq: this->frequencies) {
      k.push_back(freq.first);
    }
    return k;
  }

  void frequency_table::print() const {
    auto set = this->to_set();
    cout << "Frequency Table" << endl
         << "---------------" << endl;
    for (auto frequency : set) {
      switch (frequency->get_value().get_character()) {
        case '\n':
          cout << "\\n";
          break;
        case '\t':
          cout << "\\t";
          break;
        default:
          cout << " " << frequency->get_value().get_character();
      }
      cout << " | " << static_cast<double >(frequency->get_value().get_frequency()) * 100 /
                       static_cast<double>(this->total) << "%" << endl;
    }
    delete_huffman_frequency_set(set);
  }

  /**
   * Delete a huffman_frequency_set.
   * static since an instance isn't needed.
   * @param set
   */
  void frequency_table::delete_huffman_frequency_set(
          const std::set<huffman_tree_node *, huffman_tree_node::comparator> &set) {
    for (auto it: set) {
      delete it;
    }
  }
}
