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
    for (char c: str) {
      auto res = this->frequencies.insert({c, 1});
      if (!res.second
          && res.first != this->frequencies.end()) {
        res.first->second++;
      }
    }
  }

  void frequency_table::print_frequencies() const {
    cout << "Frequency Table" << endl
         << "---------------" << endl;
    for (auto frequency : this->frequencies) {
      switch (frequency.first) {
        case '\n':
          cout << "\\n";
          break;
        case '\t':
          cout << "\\t";
          break;
        default:
          cout << " " << frequency.first;
      }
      cout << " | " << static_cast<unsigned long>(frequency.second) * 100 / this->total << "%" << endl;
    }
  }

  /**
   * Comparator function for a type T
   */
  struct frequency_table::comp {
    //template<typename T>
    bool operator()(huffman_tree_node *l, const huffman_tree_node *r) const {
      return *l < *r;
    }
  };

  std::set<huffman_tree_node*, frequency_table::comp> frequency_table::to_set() const {
    std::set<huffman_tree_node*, comp> freq_set;
    for(auto frequency : this->frequencies) {
      auto *node = new huffman_tree_node{char_frequency{frequency.first, frequency.second, this->total}};
      freq_set.insert(node);
    }
    return freq_set;
  }

  huffman_tree_node* frequency_table::build_tree() const {
    auto freq_set = this->to_set();
    while(freq_set.size() > 1) {
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
    for(auto freq: this->frequencies) {
      k.push_back(freq.first);
    }
    return k;
  }

  /*char_frequency frequency_table::find_pair_at(const char key) const {
    auto frequency = this->frequencies.find(key);
    if (frequency == this->frequencies.end()) {
      std::string error_msg = "Could not find key ";
      error_msg += key;
      throw std::runtime_error(error_msg);
    }
    return char_frequency(frequency->first, frequency->second, this->total);
  }*/
}
