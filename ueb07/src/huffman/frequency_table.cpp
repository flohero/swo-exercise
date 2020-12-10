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
      cout << " | " << frequency.second << endl;
    }
  }

  char_frequency frequency_table::find_pair_at(const char key) const {
    auto frequency = this->frequencies.find(key);
    if (frequency == this->frequencies.end()) {
      std::string error_msg = "Could not find key ";
      error_msg += key;
      throw std::runtime_error(error_msg);
    }
    return char_frequency(frequency->first, frequency->second, this->total);
  }
}
