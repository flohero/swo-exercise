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

  std::set<huffman_tree_node *, frequency_table::comp> frequency_table::to_set() const {
    std::set<huffman_tree_node *, comp> freq_set;
    for (auto frequency : this->frequencies) {
      auto *node = new huffman_tree_node{char_frequency{frequency.first, frequency.second, this->total}};
      freq_set.insert(node);
    }
    return freq_set;
  }

  huffman_tree_node *frequency_table::build_tree() const {
    auto freq_set = this->to_set();
    while (freq_set.size() > 1) {
      huffman_tree_node *first = *freq_set.begin();
      huffman_tree_node *second = *std::next(freq_set.begin(), 1);
      huffman_tree_node *node = *first + second;
      freq_set.erase(first);
      freq_set.erase(second);
      freq_set.insert(node);
    }
    return *freq_set.begin();
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
  }
}
